/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { 
	"JetBrainsMono Nerd Font:size=10",
	"Twitter Color Emoji:style=Regular:pixelsize=20:antialias=true:autohint=true"
};
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=10";

static const char col_gray1[]       = "#292f36";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#e0fbfc";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#fcba03";
static const unsigned int baralpha = 0xf0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray1, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "﬏","4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       3 << 9,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default 0*/
	{ "[M]",      monocle }, /*1*/
	{ "[\\]",     dwindle }, /*2*/
	{ "===",      bstackhoriz }, /*3*/
	{ "﩯",        grid }, /*4*/
	{ "###",      nrowgrid }, /*5*/
	{ "---",      horizgrid }, /*6*/
	{ ":::",      gaplessgrid }, /*7*/
	{ "",      centeredmaster }, /*8*/
	{ "",      centeredfloatingmaster }, /*9*/
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include<X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,	   spawn,          SHCMD("dmenu_run -l 9 -z 600 -x 1140 -y 750") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	
	
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_k,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_r,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	
	{ MODKEY|Mod1Mask,				XK_t,			setlayout,		{.v = &layouts[0]} }, /* tile */
	{ MODKEY|Mod1Mask,				XK_f,			setlayout,		{.v = &layouts[1]} }, /* monocle */
	
	{ MODKEY|Mod1Mask,				XK_d,			setlayout,		{.v = &layouts[2]} }, /* dwindle */
	{ MODKEY|Mod1Mask,				XK_b,			setlayout,		{.v = &layouts[3]} }, /* bstack h */
	
	{ MODKEY|ShiftMask,				XK_g,			setlayout,		{.v = &layouts[5]} }, /* grid H*/
	{ MODKEY|Mod1Mask,				XK_g,			setlayout,		{.v = &layouts[6]} }, /* grid B*/
	{ MODKEY,						XK_g,			setlayout,		{.v = &layouts[7]} }, /* grid B H*/
	
	{ MODKEY,						XK_c,			setlayout,		{.v = &layouts[8]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,				XK_c,			setlayout,		{.v = &layouts[9]} }, /* centeredfloatingmaster */
	
	{ MODKEY|ShiftMask,				XK_f,			setlayout,		{ .v = &layouts[10]} },
	
	{ MODKEY|ShiftMask,             XK_space,  		togglefloating, {0} },
	{ MODKEY,						XK_f,			togglefullscr,	{0} },
	
	
	{ MODKEY,						XK_o,			incnmaster,     { .i = +1 } },
	{ MODKEY|ShiftMask,				XK_o,			incnmaster,     { .i = -1 } },
	

	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	
	/*-- Gaps --*/
	
	{ MODKEY,						XK_a,			togglegaps,		{0} },
	{ MODKEY|ShiftMask,				XK_a,			defaultgaps,	{0} },
	{ MODKEY,						XK_z,			incrgaps,		{.i = +3 } },
	{ MODKEY,						XK_x,			incrgaps,		{.i = -3 } },

	/*-- Utils --*/
	{ MODKEY|ShiftMask,				XK_p,			spawn,			SHCMD("import ~/Downloads/shots/screenshot~$(date '+%F~%T').png" ) },
	{ MODKEY|Mod1Mask,			    XK_k,			spawn,			SHCMD("keytoggle ui" ) },
	
	/*-- Mbpro Keys --*/	
	{0,		XF86XK_AudioLowerVolume,    spawn, 		SHCMD("pamixer --allow-boost -d 5; kill -36 $(pidof slblocks)")},
	{0,		XF86XK_AudioRaiseVolume,    spawn,		SHCMD("pamixer --allow-boost -i 5; kill -36 $(pidof slblocks)")},
	{0,		XF86XK_MonBrightnessUp,		spawn,		SHCMD("xbacklight -inc 15") },
	{0,		XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },
	{0,		XF86XK_PowerOff,			spawn,		SHCMD("sysact")},
	{0,		XF86XK_AudioMute,			spawn,		SHCMD("pamixer -t; kill -36 $(pidof slblocks)") },
	{0, 	XF86XK_AudioPrev,			spawn,		SHCMD("mpc prev") },
	{0, 	XF86XK_AudioNext,			spawn,		SHCMD("mpc next") },
	{0, 	XF86XK_AudioPlay,			spawn,		SHCMD("mpc toggle") },

	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	
	{ MODKEY,			            XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,           SHCMD("sysact") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigslblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigslblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigslblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

