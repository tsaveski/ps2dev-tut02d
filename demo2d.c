//---------------------------------------------------------------------------
// File:	demo2c.c
// Author:	Tony Saveski, saveski@gmail.com
//---------------------------------------------------------------------------
#include "g2.h"
#include "gs.h"

// background image
extern uint32 hover_w;
extern uint32 hover_h;
extern uint32 hover[];

// verdana font
extern uint32 verdana[];
extern uint16 verdana_tc[];

// good fonts
extern uint32 courier_new[];
extern uint32 tahoma[];
extern uint16 fixed_tc[];

extern uint32 texfont[];
extern uint32 texfont2[];
extern uint16 texfont_tc[];


static uint16 maxx, maxy;

//---------------------------------------------------------------------------
void flip_buffers(void)
{
    g2_wait_vsync();
    g2_set_visible_frame(1 - g2_get_visible_frame());
    g2_set_active_frame(1 - g2_get_active_frame());
}

//---------------------------------------------------------------------------
void font_demo(void)
{
uint32 i;

    g2_put_image(0, 0, hover_w, hover_h, hover);
    flip_buffers();
    g2_set_active_frame(g2_get_visible_frame());

    g2_set_font(texfont, 256, 128, texfont_tc);
    g2_set_font_spacing(1);

    g2_set_font_mag(1);
    g2_out_text(15, 10,  "NOW LOOK CLOSELY...");
    for(i=0; i<0x4FFFFFF; i++) {} // delay

    g2_set_font_mag(2);
    g2_out_text(15, 40,  "CLOSER!!");
    for(i=0; i<0x4FFFFFF; i++) {} // delay

    g2_set_font(courier_new, 256, 128, fixed_tc);
    g2_set_font_spacing(-5);
    g2_set_font_mag(1);
    g2_out_text(15, 100,  "The black outlines look crap at this size!");
    g2_out_text(15, 115,  "Let's try some Alpha-Blending instead...");
    for(i=0; i<0x4FFFFFF; i++) {} // delay

    g2_set_font(texfont2, 256, 128, texfont_tc);
    g2_set_font_spacing(1);
    g2_set_font_mag(2);
    g2_out_text(15, 140,  " BLENDED!!");

    g2_set_active_frame(1-g2_get_visible_frame());
    for(i=0; i<0xFFFFFFF; i++) {} // delay
}

//---------------------------------------------------------------------------
void good_bye(void)
{
uint32 i;

    g2_put_image(0, 0, hover_w, hover_h, hover);
    flip_buffers();
    g2_set_active_frame(g2_get_visible_frame());

    g2_set_font(texfont2, 256, 128, texfont_tc);
    g2_set_font_spacing(1);
    g2_set_font_mag(3);
    g2_out_text(15, 10,  "GOOD");
    g2_out_text(25, 80,  "BYE!");

    g2_set_font(courier_new, 256, 128, fixed_tc);
    g2_set_font_spacing(-5);
    g2_set_font_mag(1);
    g2_out_text(15, 160,  "I hope you're enjoying these tutorials.");
    g2_out_text(15, 175,  "And remember to share your code!");
    for(i=0; i<0x4FFFFFF; i++) {} // delay

    g2_set_active_frame(1-g2_get_visible_frame());
    for(i=0; i<0xFFFFFFF; i++) {} // delay
}

//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
uint32 i;

    argc=argc;
    argv=argv;

    if(gs_is_ntsc())
        g2_init(NTSC_512_224_32);
    else
        g2_init(PAL_512_256_32);

    maxx = g2_get_max_x();
    maxy = g2_get_max_y();

    // clear the screens and make sure visible and active
    // buffers are different.
    g2_set_active_frame(0);
    g2_set_fill_color(0, 0, 0);
    g2_fill_rect(0, 0, maxx, maxy);
    g2_set_visible_frame(0);

    g2_set_active_frame(1);
    g2_set_fill_color(0, 0, 0);
    g2_fill_rect(0, 0, maxx, maxy);

    while(1)
    {
        g2_set_active_frame(1);
        g2_set_visible_frame(0);
        g2_set_font(verdana, 256, 128, verdana_tc);
        g2_set_font_spacing(1);

        // Test crap font
        g2_set_font_mag(2);
        g2_put_image(0, 0, hover_w, hover_h, hover);
        g2_out_text(50, 50,  "THIS IS CRAP");
        g2_out_text(50, 100, "because I don't");
        g2_out_text(50, 150, "know how to use");
        g2_out_text(50, 200, "Photoshop");
        flip_buffers();
        for(i=0; i<0xFFFFFFF; i++) {} // delay

        // Start Good Font Demo
        g2_set_visible_frame(1);
        g2_set_active_frame(0);
        g2_put_image(0, 0, hover_w, hover_h, hover);
        g2_set_visible_frame(0);

        // Courier-New Fixed
        g2_set_font(courier_new, 256, 128, fixed_tc);
        g2_set_font_spacing(-5);
        g2_set_font_mag(1);

        g2_set_fill_color(0, 0, 255);
        g2_fill_rect(10, 10, maxx-10, 50);
        g2_set_color(255, 255, 0);
        g2_rect(10, 10, maxx-10, 50);

        g2_out_text(15, 15,  "This is a nice fixed width courier-new font");
        g2_out_text(15, 30,  "created with BITMAP FONT BUILDER. Looks OK!");
        for(i=0; i<0x8FFFFFF; i++) {} // delay

        // Tahoma Fixed
        g2_set_font(tahoma, 256, 128, fixed_tc);
        g2_set_font_spacing(-5);

        g2_set_fill_color(0, 0, 255);
        g2_fill_rect(10, 60, maxx-10, 100);
        g2_set_color(255, 255, 0);
        g2_rect(10, 60, maxx-10, 100);

        g2_out_text(15, 65,  "This Tahoma font was going to be variable-");
        g2_set_font_mag(1);
        g2_out_text(15, 80,  "width but I got bored with the TC's!");
        for(i=0; i<0x8FFFFFF; i++) {} // delay

        // Secret Message
        g2_set_font(courier_new, 256, 128, fixed_tc);
        g2_set_font_spacing(-5);

        g2_set_fill_color(0, 0, 255);
        g2_fill_rect(10, 110, maxx-10, 180);
        g2_set_color(255, 255, 0);
        g2_rect(10, 110, maxx-10, 180);

        g2_out_text(15, 115,  "The background image is a hint to the");
        g2_out_text(15, 130,  "famous NOW3D to port his PSX HoverDemo over");
        g2_out_text(15, 145,  "to PS2 and make the Terrain and Tank look");
        g2_out_text(15, 160,  "at least this good!");
        for(i=0; i<0x1FFFFFFF; i++) {} // delay

// Some code to help you debug set_font_color(). I have no idea why the whole
// font bitmap is not being covered with RED!
//		g2_set_font_spacing(0);
//		g2_set_font_color(255, 0, 0);
//		g2_out_text(15, 95,   "!\"#$%&'()*+,-./");
//		g2_out_text(15, 110,  "01234567890:;<=>?");
//		g2_out_text(15, 125,  "@ABCDEFGHIJKLMNO");
//		g2_out_text(15, 140,  "PQRSTUVWXYZ[\\]^_");
//		g2_out_text(15, 155,  "`abcdefghijklmno");
//		g2_out_text(15, 170,  "pqrstuvwxyz{|}~");

        g2_set_active_frame(1);

        font_demo();
        good_bye();
    }

    // ok...it will never get here...
    g2_end();
    return(0);
}
