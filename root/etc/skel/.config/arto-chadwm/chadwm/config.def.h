/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

#define TERMINAL "kitty"
#define TERMCLASS "Kitty"
#define SCREENSHOTSDIR "/home/jonathan/Pictures/Screenshots"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int default_border = 0;   /* to switch back to default border after dynamic border resizing via keybinds */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 12;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 12;       /* vert inner gap between windows */
static const unsigned int gappoh    = 12;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 12;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails,display systray on the 1st monitor,False: display systray on last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int showtab            = showtab_auto;
static const int toptab             = 1;        /* 0 means bottom tab */
static const int floatbar           = 1;/* 1 means the bar will float(don't have padding),0 means the bar have padding */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 5;        /* padding inside the bar */
static const int vertpadbar         = 11;       /* padding inside the bar */
static const int vertpadtab         = 35;
static const int horizpadtabi       = 15;
static const int horizpadtabo       = 15;
static const int scalepreview       = 4;
static const int tag_preview        = 1;        /* 1 means enable, 0 is off */
static const int colorfultag        = 1;        /* 0 means use SchemeSel for selected non vacant tag */
static const char dmenufont[]       = "JetBrainsMono Nerd Font:style:medium:size=14";
static const char col_gray1[]       = "#212337";
static const char col_gray2[]       = "#3B4252";
static const char col_gray3[]       = "#99c1f1";
static const char col_gray4[]       = "#abafbf";
static const char col_cyan[]        = "#6d8dad";
//static const char *light_up[] = {"/usr/bin/light", "-A", "5", NULL};
//static const char *light_down[] = {"/usr/bin/light", "-U", "5", NULL};
static const int new_window_attach_on_end = 0; /*  1 means the new window will attach on the end; 0 means the new window will attach on the front,default is front */
#define ICONSIZE 20   /* icon size */
#define ICONSPACING 8 /* space between icon and title */

static const char *fonts[]          = {"JetBrainsMono Nerd Font:style:medium:size=14"};

// theme
#include "themes/skylight.h"
//#include "themes/onedark.h"
//#include "themes/crimson.h"
//#include "themes/catppuccin.h"
//#include "themes/nord.h"
//#include "themes/gruvchad.h"
//#include "themes/dracula.h"

static const char *colors[][3]      = {
    /*                     fg       bg      border */
    [SchemeNorm]       = { gray3,   black,  gray2 },
    [SchemeSel]        = { gray4,   blue,   blue  },
    [SchemeTitle]      = { white,   black,  black  }, // active window title
    [TabSel]           = { blue,    gray2,  black },
    [TabNorm]          = { gray3,   black,  black },
    [SchemeTag]        = { gray3,   black,  black },
    [SchemeTag1]       = { blue,    black,  black },
    [SchemeTag2]       = { red,     black,  black },
    [SchemeTag3]       = { orange,  black,  black },
    [SchemeTag4]       = { green,   black,  black },
    [SchemeTag5]       = { blue,    black,  black },
    [SchemeTag6]       = { pinky,   black,  black },
    [SchemeTag7]       = { pink,    black,  black },
    [SchemeTag8]       = { orange,  black,  black },
    [SchemeTag9]       = { red,     black,  black },
    [SchemeLayout]     = { green,   black,  black },
    [SchemeBtnPrev]    = { green,   black,  black },
    [SchemeBtnNext]    = { yellow,  black,  black },
    [SchemeBtnClose]   = { red,     black,  black },
};

/* tagging */
//static char *tags[] = {"", "", "", "", "", "", "", "", ""};
//static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
//static char *tags[] = { "", "", "", "", "", "", "", "", "" };
//static char *tags[] = { "Web", "Chat", "Edit", "Meld", "Vb", "Mail", "Video", "Image", "Files" };
//static char *tags[] = {"一", "二", "三", "四", "五", "六", "七", "八", "九"};

static const char* thunderbird[] = { "thunderbird", "open" , "franz", NULL };
static const char* discord[] = { "discord", "open" , "discord", NULL };
static const char* code[] = { "code", "open" , "code", NULL };
static const char* mintstick[] = { "mintstick", "-m", "iso", NULL};
static const char* pavucontrol[] = { "pavucontrol", NULL };

static const Launcher launchers[] = {
    /* command     name to display */
    { thunderbird,           "數" },
    { discord,       "ﱲ" },
    { code,      "" },
    { mintstick,     "虜" },
    { pavucontrol,   "墳" },
};

static const int tagschemes[] = {
    SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5, SchemeTag6, SchemeTag7, SchemeTag8, SchemeTag9
};

static const unsigned int ulinepad      = 5; /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke   = 2; /* thickness / height of the underline */
static const unsigned int ulinevoffset  = 0; /* how far above the bottom of the bar the line should appear */
static const int ulineall               = 0; /* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
  /* class                   instance    title       tags mask     iscentered   isfloating   monitor */
  { "Gimp",                  NULL,       NULL,       0,            0,           1,           -1 },
  { "Firefox",               NULL,       NULL,       1 << 8,       0,           0,           -1 },
  { "Galculator",            NULL,       NULL,       0,            1,           1,           -1 },
  { "expressvpn-gui-gtk",    "expressvpn-gui-gtk", NULL,       0,            1,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "functions.h"


static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "[M]",      monocle },
    { "[@]",      spiral },
    { "[\\]",     dwindle },
    { "H[]",      deck },
    { "TTT",      bstack },
    { "===",      bstackhoriz },
    { "HHH",      grid },
    { "###",      nrowgrid },
    { "---",      horizgrid },
    { ":::",      gaplessgrid },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "><>",      NULL },    /* no layout function means floating behavior */
    { NULL,       NULL },
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
static const char *termcmd[]  = { TERMINAL, NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *xi[] = {"brightnessctl", "set", "+5%", NULL};
//static const char *xd[] = {"brightnessctl", "set", "5%-", NULL};
static const char *browser[] = {"firefox", NULL}; 
static const char *screenshot[] = { "flameshot", "gui", "-p", SCREENSHOTSDIR, NULL };
static const char *fullscreenshot[] = { "flameshot", "full", "-p", SCREENSHOTSDIR, NULL };
static const char *delayfullscreenshot[] = { "flameshot", "full", "-p", SCREENSHOTSDIR, "-d", "2000", NULL };
static const char *calculatorcmd[] = { "galculator",  NULL };
static const char *thunarcmd[] = { "thunar",  NULL };
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *pausplaycmd[] = { "playerctl", "play-pause", NULL };
static const char *stopplaycmd[] = { "playerctl", "stop", NULL };
static const char *nextplaycmd[] = { "playerctl", "next", NULL };
static const char *prevplaycmd[] = { "playerctl", "previous", NULL };
static const char *emacscmd[] = { "emacs", NULL };
static const char *xkillcmd[] = { "xkill", NULL };
static const char *buildcmd[] = { "sh", "/usr/local/bin/artolinux-chadwm-build", NULL };

static Key keys[] = {
    // brightness and audio
    /* modifier                         key         function        argument */
    //{0,             XF86XK_MonBrightnessDown,       spawn,          {.v = xd}},
    //{0,             XF86XK_MonBrightnessUp,         spawn,          {.v = xi}},
    //{0,             XF86XK_AudioRaiseVolume,        spawn,          {.v = upvol}},
    //{0,             XF86XK_AudioLowerVolume,        spawn,          {.v = downvol}},
    //{0,             XF86XK_AudioMute,               spawn,          {.v = mutevol}},
    { 0,                            0x1008ff02, spawn,         SHCMD ("xbacklight -inc 10")},
    { 0,                            0x1008ff03, spawn,         SHCMD ("xbacklight -dec 10")},

//Screenshots
    //{ MODKEY|Mod1Mask,              XK_k,      spawn,          {.v = altkeycmd } },
    //{ MODKEY|Mod1Mask,              XK_l,      spawn,          {.v = screensavercmd } },
    /* This works with a keyboard with Print Screen key*/
    { MODKEY,                       XK_Print,  spawn,          {.v = screenshot } },
    { 0,                            XK_Print,  spawn,          {.v = fullscreenshot } },
    { Mod1Mask,                     XK_Print,  spawn,          {.v = delayfullscreenshot } },
   
    // launch applications
    { MODKEY,                           XK_t,   spawn,       {.v = termcmd}},
    { MODKEY|ShiftMask,               XK_f,   spawn,       {.v = thunarcmd}},
    { MODKEY,                           XK_e,   spawn,       {.v = emacscmd}},
    { MODKEY,                           XK_w,   spawn,       {.v = browser}},
    { MODKEY,                           XK_v,   spawn,       SHCMD("pavucontrol")},
    { MODKEY,                           XK_m,   spawn,       SHCMD("xfce4-settings-manager")},
    { MODKEY,                           XK_d,   spawn,       {.v = dmenucmd}},
    { 0, XF86XK_Calculator,         spawn,                     {.v = calculatorcmd}},
    { 0, XF86XK_WWW,                spawn,                     {.v = browser}},
    { 0, XF86XK_Explorer,           spawn,                     {.v = thunarcmd}},

    //Audio keybinds
    { 0, XF86XK_AudioMute,          spawn,                     {.v = mutevol}},
    { 0, XF86XK_AudioMicMute,       spawn,                     SHCMD("pactl set-source-mute @DEFAULT_SINK@ toggle") },
    { 0, XF86XK_AudioRaiseVolume,   spawn,                     {.v = upvol}},
    { 0, XF86XK_AudioLowerVolume,   spawn,                     {.v = downvol}},
    { 0, XF86XK_AudioPlay,          spawn,                     {.v = pausplaycmd} },
    { 0, XF86XK_AudioStop,          spawn,                     {.v = stopplaycmd} },
    { 0, XF86XK_AudioPrev,          spawn,                     {.v = prevplaycmd} },
    { 0, XF86XK_AudioNext,          spawn,                     {.v = nextplaycmd} },

    // toggle stuff
    { MODKEY,                           XK_b,       togglebar,      {0} },
    { MODKEY|ControlMask,               XK_t,       togglegaps,     {0} },
    { MODKEY|ShiftMask,                 XK_space,   togglefloating, {0} },
    { MODKEY,                           XK_f,       togglefullscr,  {0} },

    { MODKEY|ControlMask,               XK_w,       tabmode,        { -1 } },
    { MODKEY,                           XK_j,       focusstack,     {.i = +1 } },
    { MODKEY,                           XK_k,       focusstack,     {.i = -1 } },
    { MODKEY,                           XK_i,       incnmaster,     {.i = +1 } },
    { MODKEY,                           XK_g,       incnmaster,     {.i = -1 } },

    // shift view
    { MODKEY,                           XK_Left,    shiftview,      {.i = -1 } },
    { MODKEY,                           XK_Right,   shiftview,      {.i = +1 } },

    // change m,cfact sizes 
    { MODKEY,                           XK_h,       setmfact,       {.f = -0.05} },
    { MODKEY,                           XK_l,       setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,                 XK_h,       setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,                 XK_l,       setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,                 XK_o,       setcfact,       {.f =  0.00} },


    { MODKEY|ShiftMask,                 XK_j,       movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,                 XK_k,       movestack,      {.i = -1 } },
    { MODKEY|ShiftMask,                 XK_Return,  zoom,           {0} },
    { MODKEY,                           XK_Tab,     view,           {0} },

    // overall gaps
    { MODKEY|ControlMask,               XK_i,       incrgaps,       {.i = +1 } },
    { MODKEY|ControlMask,               XK_d,       incrgaps,       {.i = -1 } },

    // inner gaps
    { MODKEY|ShiftMask,                 XK_i,       incrigaps,      {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask,     XK_i,       incrigaps,      {.i = -1 } },

    // outer gaps
    { MODKEY|ControlMask,               XK_o,       incrogaps,      {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask,     XK_o,       incrogaps,      {.i = -1 } },

    // inner+outer hori, vert gaps 
    { MODKEY|ControlMask,               XK_6,       incrihgaps,     {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask,     XK_6,       incrihgaps,     {.i = -1 } },
    { MODKEY|ControlMask,               XK_7,       incrivgaps,     {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask,     XK_7,       incrivgaps,     {.i = -1 } },
    { MODKEY|ControlMask,               XK_8,       incrohgaps,     {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask,     XK_8,       incrohgaps,     {.i = -1 } },
    { MODKEY|ControlMask,               XK_9,       incrovgaps,     {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask,     XK_9,       incrovgaps,     {.i = -1 } },

    { MODKEY|ControlMask|ShiftMask,     XK_d,       defaultgaps,    {0} },

    // layout
    { MODKEY,                           XK_y,       setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,                 XK_y,       setlayout,      {.v = &layouts[1]} },
    { MODKEY|ControlMask,                           XK_m,       setlayout,      {.v = &layouts[2]} },
    { MODKEY|ControlMask,               XK_g,       setlayout,      {.v = &layouts[10]} },
    { MODKEY|ControlMask|ShiftMask,     XK_t,       setlayout,      {.v = &layouts[13]} },
    { MODKEY,                           XK_space,   setlayout,      {0} },
    { MODKEY|ControlMask,               XK_comma,   cyclelayout,    {.i = -1 } },
    { MODKEY|ControlMask,               XK_period,  cyclelayout,    {.i = +1 } },
    { MODKEY,                           XK_0,       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,                 XK_0,       tag,            {.ui = ~0 } },
    { MODKEY,                           XK_comma,   focusmon,       {.i = -1 } },
    { MODKEY,                           XK_period,  focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,                 XK_Left,    tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,                 XK_Right,   tagmon,         {.i = +1 } },

    // change border size
    { MODKEY|ShiftMask,                 XK_minus,   setborderpx,    {.i = -1 } },
    { MODKEY|ShiftMask,                 XK_p,       setborderpx,    {.i = +1 } },
    { MODKEY|ShiftMask,                 XK_w,       setborderpx,    {.i = default_border } },

    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)

    // kill dwm/manage desktop
    { MODKEY|ControlMask,               XK_x,       spawn,        SHCMD("systemctl reboot")},
    { MODKEY|ShiftMask,               XK_x,       spawn,         SHCMD("systemctl poweroff")},
    { MODKEY,                           XK_x,   spawn,       SHCMD("pkill chadwm; pkill -f bar.sh; pkill run.sh")},

    // kill window
    { MODKEY,                           XK_q,       killclient,     {0} },
    { MODKEY,                           XK_Escape,       spawn,     {.v = xkillcmd} },

    // restart
    { MODKEY,                           XK_r,       restart,           {0} },
    { MODKEY|ShiftMask,                 XK_r,       spawn,           {.v = buildcmd}},

    // hide & restore windows
    { MODKEY|ControlMask,               XK_e,       hidewin,        {0} },
    { MODKEY|ShiftMask,                 XK_e,       restorewin,     {0} },

    // qwerty keyboard

    TAGKEYS(                            XK_1,                       0)
    TAGKEYS(                            XK_2,                       1)
    TAGKEYS(                            XK_3,                       2)
    TAGKEYS(                            XK_4,                       3)
    TAGKEYS(                            XK_5,                       4)
    TAGKEYS(                            XK_6,                       5)
    TAGKEYS(                            XK_7,                       6)
    TAGKEYS(                            XK_8,                       7)
    TAGKEYS(                            XK_9,                       8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },

    /* Keep movemouse? */
    /* { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} }, */

    /* placemouse options, choose which feels more natural:
    *    0 - tiled position is relative to mouse cursor
    *    1 - tiled position is relative to window center
    *    2 - mouse pointer warps to window center
    *
    * The moveorplace uses movemouse or placemouse depending on the floating state
    * of the selected client. Set up individual keybindings for the two if you want
    * to control these separately (i.e. to retain the feature to move a tiled window
    * into a floating position).
    */
    { ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkClientWin,         ControlMask,    Button1,        dragmfact,      {0} },
    { ClkClientWin,         ControlMask,    Button3,        dragcfact,      {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTabPrev,           0,              Button1,        movestack,      { .i = -1 } },
    { ClkTabNext,           0,              Button1,        movestack,      { .i = +1 } },
    { ClkTabClose,          0,              Button1,        killclient,     {0} },
};
