// gps.chip.c - Wokwi Custom Chip: NMEA GPS Simulator
// Zero stdlib dependencies - WASM compatible

#include "wokwi-api.h"

#define NULL ((void*)0)
#define BAUD_RATE    115200
#define INTERVAL_MS  100
#define NUM_SATS     8
#define CRUISE_MPH   55.0
#define HEADING_DEG  45.0
#define EARTH_R      6371000.0
#define M_PI         3.14159265358979323846
#define DEG2RAD(d)   ((d) * M_PI / 180.0)
#define RAD2DEG(r)   ((r) * 180.0 / M_PI)
#define MPH_TO_KTS(v) ((v) * 0.868976)
#define MPH_TO_MPS(v) ((v) * 0.44704)

// ── Zero-dependency math ──────────────────────────────────────
static double my_sin(double x) {
    while (x >  M_PI) x -= 2*M_PI;
    while (x < -M_PI) x += 2*M_PI;
    double r=x, t=x, x2=x*x;
    t*=-x2/(2*3);   r+=t;
    t*=-x2/(4*5);   r+=t;
    t*=-x2/(6*7);   r+=t;
    t*=-x2/(8*9);   r+=t;
    t*=-x2/(10*11); r+=t;
    return r;
}
static double my_cos(double x) { return my_sin(x + M_PI/2.0); }
static double my_asin(double x) {
    double x2=x*x;
    return x*(1.0+x2*(1.0/6.0+x2*(3.0/40.0+x2*15.0/336.0)));
}
static double my_atan2(double y, double x) {
    if (x==0.0) return y>0 ? M_PI/2 : -M_PI/2;
    double r=y/x, a=r/(1.0+0.28125*r*r);
    if (x<0) a+=(y>=0)?M_PI:-M_PI;
    return a;
}
static double my_sqrt(double x) {
    if (x<=0) return 0;
    double r=x*0.5;
    for(int i=0;i<20;i++) r=(r+x/r)*0.5;
    return r;
}

// ── Zero-dependency string/mem ────────────────────────────────
__attribute__((used)) void *memcpy(void *d, const void *s, int n) {
    char *dd=(char*)d; const char *ss=(const char*)s;
    void *r=d; while(n--) *dd++=*ss++;
    return r;
}
__attribute__((used)) void *memset(void *d, int c, int n) {
    char *dd=(char*)d; void *r=d; while(n--) *dd++=(char)c;
    return r;
}

// Write exactly `digits` digits from unsigned int, zero-padded
static int uint_fixed(char *buf, unsigned int val, int digits) {
    for(int i=digits-1;i>=0;i--){ buf[i]='0'+(val%10); val/=10; }
    buf[digits]=0; return digits;
}

// Write double as iiii.ffff (int_d integer digits, frac_d fractional)
static int dbl_fmt(char *buf, double val, int int_d, int frac_d) {
    int neg=(val<0); if(neg) val=-val;
    unsigned int ip=(unsigned int)val;
    double frac=val-ip;
    int pos=0;
    if(neg) buf[pos++]='-';
    pos+=uint_fixed(buf+pos, ip, int_d);
    buf[pos++]='.';
    for(int i=0;i<frac_d;i++){
        frac*=10.0; int d=(int)frac;
        buf[pos++]='0'+d; frac-=d;
    }
    buf[pos]=0; return pos;
}

// Convert decimal degrees to NMEA dddmm.mmmm
static int deg_nmea(char *buf, double deg, int is_lat) {
    if(deg<0) deg=-deg;
    int d=(int)deg;
    double m=(deg-d)*60.0;
    int pos=uint_fixed(buf, d, is_lat?2:3);
    pos+=dbl_fmt(buf+pos, m, 2, 4);
    return pos;
}

static int app(char *b, int p, const char *s) {
    while(*s) b[p++]=*s++; return p;
}

// ── NMEA checksum ─────────────────────────────────────────────
static uint8_t nmea_cs(const char *s) {
    uint8_t cs=0;
    for(const char *p=s+1; *p && *p!='*'; p++) cs^=(uint8_t)*p;
    return cs;
}
static void hex2(char *buf, uint8_t v) {
    const char *h="0123456789ABCDEF";
    buf[0]=h[v>>4]; buf[1]=h[v&0xF]; buf[2]=0;
}

// ── Sentence builders ─────────────────────────────────────────
static int build_gga(char *out, double lat, double lon, double elapsed_s) {
    int hh=((int)elapsed_s/3600)%24;
    int mm=((int)elapsed_s/60)%60;
    int ss=(int)elapsed_s%60;
    char st[8]; uint_fixed(st,hh,2); uint_fixed(st+2,mm,2); uint_fixed(st+4,ss,2); st[6]=0;
    char slat[16], slon[16], shex[4];
    deg_nmea(slat, lat, 1);
    deg_nmea(slon, lon, 0);
    char body[128]; int p=0;
    p=app(body,p,"$GPGGA,"); p=app(body,p,st); p=app(body,p,".00,");
    p=app(body,p,slat); body[p++]=','; body[p++]=(lat>=0?'N':'S'); body[p++]=',';
    p=app(body,p,slon); body[p++]=','; body[p++]=(lon>=0?'E':'W'); body[p++]=',';
    body[p++]='1'; body[p++]=',';
    uint_fixed(body+p,NUM_SATS,2); p+=2;
    p=app(body,p,",1.2,100.0,M,0.0,M,,");
    body[p]=0;
    hex2(shex, nmea_cs(body));
    body[p++]='*'; body[p++]=shex[0]; body[p++]=shex[1];
    body[p++]='\r'; body[p++]='\n'; body[p]=0;
    memcpy(out, body, p+1);
    return p;
}

static int build_rmc(char *out, double lat, double lon, double elapsed_s, double speed_mph) {
    int hh=((int)elapsed_s/3600)%24;
    int mm=((int)elapsed_s/60)%60;
    int ss=(int)elapsed_s%60;
    char st[8]; uint_fixed(st,hh,2); uint_fixed(st+2,mm,2); uint_fixed(st+4,ss,2); st[6]=0;
    char slat[16], slon[16], sspd[12], shex[4];
    deg_nmea(slat, lat, 1);
    deg_nmea(slon, lon, 0);
    dbl_fmt(sspd, MPH_TO_KTS(speed_mph), 2, 2);
    char body[128]; int p=0;
    p=app(body,p,"$GPRMC,"); p=app(body,p,st); p=app(body,p,".00,A,");
    p=app(body,p,slat); body[p++]=','; body[p++]=(lat>=0?'N':'S'); body[p++]=',';
    p=app(body,p,slon); body[p++]=','; body[p++]=(lon>=0?'E':'W'); body[p++]=',';
    p=app(body,p,sspd);
    p=app(body,p,",45.00,040326,0.0,E");
    body[p]=0;
    hex2(shex, nmea_cs(body));
    body[p++]='*'; body[p++]=shex[0]; body[p++]=shex[1];
    body[p++]='\r'; body[p++]='\n'; body[p]=0;
    memcpy(out, body, p+1);
    return p;
}

// ── Position advance ──────────────────────────────────────────
static void advance(double *lat, double *lon, double dist_m) {
    double bear=DEG2RAD(HEADING_DEG);
    double latr=DEG2RAD(*lat), lonr=DEG2RAD(*lon);
    double ang=dist_m/EARTH_R;
    double nlat=my_asin(my_sin(latr)*my_cos(ang)+my_cos(latr)*my_sin(ang)*my_cos(bear));
    double nlon=lonr+my_atan2(my_sin(bear)*my_sin(ang)*my_cos(latr),
                               my_cos(ang)-my_sin(latr)*my_sin(nlat));
    *lat=RAD2DEG(nlat); *lon=RAD2DEG(nlon);
}

// ── Chip state ────────────────────────────────────────────────
typedef struct {
    uart_dev_t uart;
    timer_t    timer;
    double     lat, lon, speed_mph, elapsed_s;
    char       tx_buf[256];
    uint32_t   tx_len, tx_pos;
} chip_t;

static chip_t chip;

static void on_write_done(void *ud) {
    chip_t *c=(chip_t*)ud;
    if(c->tx_pos < c->tx_len) {
        uint32_t rem=c->tx_len-c->tx_pos;
        uint32_t chunk=rem>64?64:rem;
        uart_write(c->uart,(uint8_t*)(c->tx_buf+c->tx_pos),chunk);
        c->tx_pos+=chunk;
    }
}

static void on_timer(void *ud) {
    chip_t *c=(chip_t*)ud;
    double dt=INTERVAL_MS/1000.0;
    c->elapsed_s+=dt;
    if(c->speed_mph < CRUISE_MPH) {
        c->speed_mph+=5.0*dt;
        if(c->speed_mph>CRUISE_MPH) c->speed_mph=CRUISE_MPH;
    }
    if(c->speed_mph>1.5) advance(&c->lat,&c->lon,MPH_TO_MPS(c->speed_mph)*dt);

    char tmp[160];
    c->tx_len=0;
    int n=build_gga(tmp, c->lat, c->lon, c->elapsed_s);
    memcpy(c->tx_buf+c->tx_len, tmp, n); c->tx_len+=n;
    n=build_rmc(tmp, c->lat, c->lon, c->elapsed_s, c->speed_mph);
    memcpy(c->tx_buf+c->tx_len, tmp, n); c->tx_len+=n;

    c->tx_pos=0;
    uint32_t first=c->tx_len>64?64:c->tx_len;
    uart_write(c->uart,(uint8_t*)c->tx_buf,first);
    c->tx_pos=first;
}

void chip_init(void) {
    memset(&chip, 0, sizeof(chip));
    chip.lat=40.712776; chip.lon=-74.005974;
    const uart_config_t ucfg = {
        .tx        = pin_init("TX", INPUT_PULLUP),
        .rx        = pin_init("RX", INPUT),
        .baud_rate = BAUD_RATE,
        .rx_data   = NULL,
        .write_done= on_write_done,
        .user_data = &chip,
    };
    chip.uart=uart_init(&ucfg);
    const timer_config_t tcfg = {
        .callback = on_timer,
        .user_data= &chip,
    };
    chip.timer=timer_init(&tcfg);
    timer_start(chip.timer, INTERVAL_MS*1000, true);
}
