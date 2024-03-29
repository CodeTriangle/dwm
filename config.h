/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gap pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "tewi:size=9" };
static const char dmenufont[]       = "tewi:size=9";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#888888";
static const char col_gray4[]       = "#bbbbbb";
static const char col_gray5[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_ored1[]       = "#ff4500";
static const char col_ored2[]       = "#992900";
static const char col_mprp1[]       = "MediumPurple4";
static const char col_mprp2[]       = "MediumPurple"; 
static const char col_mprp3[]       = "MediumPurple1";
static const char col_gbbg1[]       = "#3c3836";
static const char col_gbfg4[]       = "#a89984";
static const char col_gbgr[]        = "#928374";
static const char col_gbfg3[]       = "#bdae93";
static const char col_gbbg4[]       = "#7c6f64";
static const char col_gbfg1[]       = "#ebdbb2";
static const char col_gbfg0[]       = "#fbf1c7";
static const char col_gbbg2[]       = "#584945";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gbfg3, col_gbbg4, col_gbfg4 },
	[SchemeSel]  = { col_gbfg4, col_gbbg1, col_gbfg4 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7" };
static const char *alttags[] = { "1*", "2*", "3*", "4*", "5*", "6*", "7*" };

static const char *tagsel[][3] = {
        { col_gbfg0, col_gbbg2, col_gbfg4 }, // all
	{ "#1d2021", "#cc241d", "#fb4944" },// "#9d0006" }, //  // red
	{ "#1d2021", "#d65d0e", "#fe8019" },// "#af3a03" }, //  // orange
	{ "#1d2021", "#d79921", "#fabd2f" },// "#b57614" }, //  // yellow
	{ "#1d2021", "#98971a", "#b8bb26" },// "#79740e" }, //  // green
	{ "#1d2021", "#689d6a", "#7ec068" },//"#8ec07c" },// "#427b58" }, //  // cyan
	{ "#1d2021", "#458588", "#15a598" },// "#83a598" },// "#076678" }, //  // blue
	{ "#1d2021", "#b16286", "#d85aa6" },//"#d3869b" },// "#8f3f71" }, //  // magenta
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance      title           tags mask     isfloating   monitor */
	{ "Gimp",             NULL,         NULL,           0,            1,           -1 },
	{ "firefox",          "Navigator",  NULL,           1 << 1,       0,           -1 },
	{ "firefox",          "Toolkit",    NULL,           1 << 1,       1,           -1 },
	{ "Thunderbird",      "Mail",       NULL,           1 << 2,       0,           -1 },
	{ "Thunderbird",      "Msgcompose", NULL,           1 << 3,       0,           -1 },
	{ "jetbrains-studio", NULL,         NULL,           1 << 4,       1,           -1 },
        { "XClipboard",       NULL,         NULL,           0,            1,           -1 },
        { "feh",              "feh",        NULL,           0,            1,           -1 },
        { "discord",          NULL,         NULL,           1 << 4,       0,           -1 },
        { "Steam",            NULL,         NULL,           1 << 5,       0,           -1 },
        { "Steam",            NULL,         "News",         0,            1,           -1 },
        { "zoom",             "zoom",       "Account",      1 << 6,       0,           -1 },
        { "zoom",             "zoom",       "Meeting",      1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
        { "|||",      deck },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static char dmenusb[8];
static char dmenusf[8];
static const char *dmenucmd[]   = {
    "dmenu_run", "-m", dmenumon, "-g", "7", "-l", "5",
    "-nb", col_gbbg1, "-nf", col_gbfg4,
    "-sb", dmenusb, "-sf", dmenusf,
    "-fn", dmenufont,
};

static const char *termcmd[]    = { "st", NULL };
static const char *tmuxcmd[]    = { "st", "-e", "tmux", NULL };
static const char *attachcmd[]  = { "st", "-e", "tmux", "attach", NULL };

static const char *ffoxcmd[]    = { "firefox", NULL };
static const char *tbirdcmd[]   = { "tbird", NULL };

static const char *volupcmd[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%",    NULL };
static const char *voldncmd[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%",    NULL };
static const char *volmtcmd[]   = { "pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle", NULL };

static const char *xblupcmd[]   = { "xbacklight", "+10", NULL };
static const char *xbldncmd[]   = { "xbacklight", "-10", NULL };

static const char *sleepcmd[]   = { "sudo", "-A", "zzz", NULL };

static const char *scrotcmd[]  = { "scrot", "-f", "-e", "xclip -selection clipboard -t image/png -i $f ; mv $f screenshots ; ln -sf screenshots/$f ss.png", NULL };
static const char *scrotscmd[] = { "scrot", "-s", "-f", "-e", "xclip -selection clipboard -t image/png -i $f ; mv $f screenshots ; ln -sf screenshots/$f ss.png", NULL };

static const char *xclipcmd[]   = { "xclipboard", "-bg", "rgb:5/8/9", "-fg", "rgb:D/D/D", "-bd", "rgb:C/C/C", "-fn", "-*-tewi-medium-r-*-*-11-*-*-*-*-*-*-*", "-geometry", "300x50+0-0", NULL };

static const char *swmapcmd[]   = { "switchmap", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_bracketleft, spawn,     {.v = tmuxcmd } },
	{ MODKEY,                       XK_bracketright, spawn,    {.v = attachcmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = ffoxcmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = tbirdcmd } },
	{ MODKEY,                       XK_F8,     spawn,          {.v = volupcmd } },
	{ MODKEY,                       XK_F7,     spawn,          {.v = voldncmd } },
	{ MODKEY,                       XK_F6,     spawn,          {.v = volmtcmd } },
	{ MODKEY,                       XK_F4,     spawn,          {.v = swmapcmd } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = xblupcmd } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = xbldncmd } },
	{ MODKEY,                       XK_F1,     spawn,          {.v = sleepcmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = scrotcmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = scrotscmd } },
        { MODKEY,                       XK_c,      spawn,          {.v = xclipcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask,           XK_q,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

