/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2020  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#include"../picsimlab1.h"
#include"../picsimlab4.h"
#include"../picsimlab5.h"
#include"part_step.h"

/* outputs */
enum
{
 O_P1, O_P2, O_P3, O_P4, O_L1, O_L2, O_L3, O_L4, O_ROT
};

cpart_step::cpart_step(unsigned x, unsigned y)
:font (9, lxFONTFAMILY_TELETYPE, lxFONTSTYLE_NORMAL, lxFONTWEIGHT_BOLD)
{
 X = x;
 Y = y;
 ReadMaps ();

 lxImage image (&Window5);
 image.LoadFile (Window1.GetSharePath () + lxT ("parts/") + GetPictureFileName (), Orientation, Scale, Scale);

 Bitmap = new lxBitmap (&image, &Window5);
 image.Destroy ();

 canvas.Create (Window5.GetWWidget (), Bitmap);

 angle = 0;

 input_pins[0] = 0;
 input_pins[1] = 0;
 input_pins[2] = 0;
 input_pins[3] = 0;

 b1[0] = 0;
 b1[1] = 0;
 b2[0] = 0;
 b2[1] = 0;

}

cpart_step::~cpart_step(void)
{
 delete Bitmap;
 canvas.Destroy ();
}

void
cpart_step::Draw(void)
{
 float x2, y2;
 int i;
 const picpin * ppins = Window5.GetPinsValues ();

 canvas.Init (Scale, Scale, Orientation);
 canvas.SetFont (font);

 for (i = 0; i < outputc; i++)
  {

   switch (output[i].id)
    {
    case O_P1:
    case O_P2:
    case O_P3:
    case O_P4:
     canvas.SetColor (49, 61, 99);
     canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2 - output[i].x1, output[i].y2 - output[i].y1);
     canvas.SetFgColor (255, 255, 255);
     if (input_pins[output[i].id - O_P1] == 0)
      canvas.RotatedText ("NC", output[i].x1, output[i].y1, 0);
     else
      canvas.RotatedText (Window5.GetPinName (input_pins[output[i].id - O_P1]), output[i].x1, output[i].y1, 0);
     break;
    case O_ROT:
     canvas.SetColor (77, 77, 77);
     canvas.Circle (1, output[i].x1, output[i].y1, output[i].r + 10);
     canvas.SetFgColor (0, 0, 0);
     canvas.SetBgColor (250, 250, 250);
     canvas.Circle (1, output[i].x1, output[i].y1, output[i].r);
     canvas.SetBgColor (55, 55, 55);
     canvas.Circle (1, output[i].x1, output[i].y1, output[i].r / 3);
     canvas.SetLineWidth (8);
     x2 = output[i].x1 + (output[i].r - 2) * sin (angle);
     y2 = output[i].y1 + (output[i].r - 2) * cos (angle);
     canvas.Line (output[i].x1, output[i].y1, x2, y2);
     canvas.SetLineWidth (6);
     canvas.SetFgColor (77, 77, 77);
     canvas.Line (output[i].x1, output[i].y1, x2, y2);
     canvas.SetLineWidth (1);
     break;
    case O_L1:
    case O_L2:
    case O_L3:
    case O_L4:
     canvas.SetFgColor (0, 0, 0);
     if (input_pins[output[i].id - O_L1] > 0)
      {
       canvas.SetBgColor (ppins[input_pins[output[i].id - O_L1] - 1].oavalue, 0, 0);
      }
     else
      {
       canvas.SetBgColor (55, 0, 0);
      }
     //draw a LED
     color1 = canvas.GetBgColor ();
     int r = color1.Red () - 120;
     int g = color1.Green () - 120;
     int b = color1.Blue () - 120;
     if (r < 0)r = 0;
     if (g < 0)g = 0;
     if (b < 0)b = 0;
     color2.Set (r, g, b);
     canvas.SetBgColor (color2);
     canvas.Circle (1, output[i].x1, output[i].y1, output[i].r + 1);
     canvas.SetBgColor (color1);
     canvas.Circle (1, output[i].x1, output[i].y1, output[i].r - 2);
     break;
    }


  }

 canvas.End ();

}

#define STEP (1.8*M_PI/180.0)
#define HSTEP (STEP/2.0)

void
cpart_step::Process(void)
{
 const picpin * ppins = Window5.GetPinsValues ();

 if ((input_pins[0] > 0)
     &&(input_pins[1] > 0)
     &&(input_pins[2] > 0)
     &&(input_pins[3] > 0))
  {

   b1[1] = b1[0];
   b1[0] = ppins[input_pins[0] - 1].value - ppins[input_pins[2] - 1].value;
   b2[1] = b2[0];
   b2[0] = ppins[input_pins[1] - 1].value - ppins[input_pins[3] - 1].value;

   /*
   if((b1[1] != b1[0])||(b2[1] != b2[0]))
    {
     unsigned char code=ppins[input_pins[0] - 1].value  | (ppins[input_pins[1] - 1].value<<1) |  (ppins[input_pins[2] - 1].value<<2) |  (ppins[input_pins[3] - 1].value <<3);
      printf("%3i %3i %3i %3i  angle=%f  0x%02X\n",b1[0],b2[0],b1[1],b2[1],angle,code);
    }
    */

   //foward full step
   if ((b1[0] == 1) && (b2[0] == 0) && (b1[1] == 0) && (b2[1] == -1)) //0001
    angle += STEP;

   if ((b1[0] == 0) && (b2[0] == 1) && (b1[1] == 1) && (b2[1] == 0)) //0010
    angle += STEP;

   if ((b1[0] == -1) && (b2[0] == 0) && (b1[1] == 0) && (b2[1] == 1)) //0100
    angle += STEP;

   if ((b1[0] == 0)&& (b2[0] == -1) && (b1[1] == -1) && (b2[1] == 0)) //1000
    angle += STEP;

   //foward full step double phase
   if ((b1[0] == 1) && (b2[0] == 1) && (b1[1] == 1) && (b2[1] == -1)) //0011
    angle += STEP;

   if ((b1[0] == -1) && (b2[0] == 1) && (b1[1] == 1) && (b2[1] == 1)) //0110
    angle += STEP;

   if ((b1[0] == -1) && (b2[0] == -1) && (b1[1] == -1) && (b2[1] == 1)) //1100
    angle += STEP;

   if ((b1[0] == 1)&& (b2[0] == -1) && (b1[1] == -1) && (b2[1] == -1)) //1001
    angle += STEP;

   //foward half step
   if ((b1[0] == 1) && (b2[0] == 0) && (b1[1] == 1) && (b2[1] == -1))
    angle += HSTEP;

   if ((b1[0] == 1) && (b2[0] == 1) && (b1[1] == 1) && (b2[1] == 0))
    angle += HSTEP;

   if ((b1[0] == 0) && (b2[0] == 1) && (b1[1] == 1) && (b2[1] == 1))
    angle += HSTEP;

   if ((b1[0] == -1) && (b2[0] == 1) && (b1[1] == 0) && (b2[1] == 1))
    angle += HSTEP;

   if ((b1[0] == -1) && (b2[0] == 0) && (b1[1] == -1) && (b2[1] == 1))
    angle += HSTEP;

   if ((b1[0] == -1) && (b2[0] == -1) && (b1[1] == -1) && (b2[1] == 0))
    angle += HSTEP;

   if ((b1[0] == 0)&& (b2[0] == -1) && (b1[1] == -1) && (b2[1] = -1))
    angle += HSTEP;

   if ((b1[0] == 1)&& (b2[0] == -1) && (b1[1] == 0) && (b2[1] == -1))
    angle += HSTEP;


   //backward full step
   if ((b1[0] == 0) && (b2[0] == -1) && (b1[1] == 1) && (b2[1] == 0)) //1000
    angle -= STEP;

   if ((b1[0] == 1) && (b2[0] == 0) && (b1[1] == 0) && (b2[1] == 1)) //0001
    angle -= STEP;

   if ((b1[0] == 0) && (b2[0] == 1) && (b1[1] == -1) && (b2[1] == 0)) //0010
    angle -= STEP;

   if ((b1[0] == -1) && (b2[0] == 0) && (b1[1] == 0)&& (b2[1] == -1)) //0100
    angle -= STEP;

   //backward full step double phase
   if ((b1[0] == -1) && (b2[0] == -1) && (b1[1] == 1) && (b2[1] == -1)) //0011
    angle -= STEP;

   if ((b1[0] == -1) && (b2[0] == 1) && (b1[1] == -1) && (b2[1] == -1)) //0110
    angle -= STEP;

   if ((b1[0] == 1) && (b2[0] == 1) && (b1[1] == -1) && (b2[1] == 1)) //1100
    angle -= STEP;

   if ((b1[0] == 1)&& (b2[0] == -1) && (b1[1] == 1) && (b2[1] == 1)) //1001
    angle -= STEP;


   //backward half step
   if ((b1[1] == 1) && (b2[1] == 0) && (b1[0] == 1) && (b2[0] == -1))
    angle -= HSTEP;

   if ((b1[1] == 1) && (b2[1] == 1) && (b1[0] == 1) && (b2[0] == 0))
    angle -= HSTEP;

   if ((b1[1] == 0) && (b2[1] == 1) && (b1[0] == 1) && (b2[0] == 1))
    angle -= HSTEP;

   if ((b1[1] == -1) && (b2[1] == 1) && (b1[0] == 0) && (b2[0] == 1))
    angle -= HSTEP;

   if ((b1[1] == -1) && (b2[1] == 0) && (b1[0] == -1) && (b2[0] == 1))
    angle -= HSTEP;

   if ((b1[1] == -1) && (b2[1] == -1) && (b1[0] == -1) && (b2[0] == 0))
    angle -= HSTEP;

   if ((b1[1] == 0)&& (b2[1] == -1) && (b1[0] == -1) && (b2[0] = -1))
    angle -= HSTEP;

   if ((b1[1] == 1)&& (b2[1] == -1) && (b1[0] == 0) && (b2[0] == -1))
    angle -= HSTEP;

   if (angle >= 2 * M_PI)angle -= 2 * M_PI;

   if (angle <= -2 * M_PI)angle += 2 * M_PI;

  }
}

unsigned short
cpart_step::get_in_id(char * name)
{
 printf ("Erro input '%s' don't have a valid id! \n", name);
 return -1;
}

unsigned short
cpart_step::get_out_id(char * name)
{

 if (strcmp (name, "PN_1") == 0)return O_P1;
 if (strcmp (name, "PN_2") == 0)return O_P2;
 if (strcmp (name, "PN_3") == 0)return O_P3;
 if (strcmp (name, "PN_4") == 0)return O_P4;
 if (strcmp (name, "LD_1") == 0)return O_L1;
 if (strcmp (name, "LD_2") == 0)return O_L2;
 if (strcmp (name, "LD_3") == 0)return O_L3;
 if (strcmp (name, "LD_4") == 0)return O_L4;
 if (strcmp (name, "DG_ROT") == 0)return O_ROT;

 printf ("Erro output '%s' don't have a valid id! \n", name);
 return 1;
}

lxString
cpart_step::WritePreferences(void)
{
 char prefs[256];

 sprintf (prefs, "%hhu,%hhu,%hhu,%hhu", input_pins[0], input_pins[1], input_pins[2], input_pins[3]);

 return prefs;
}

void
cpart_step::ReadPreferences(lxString value)
{
 sscanf (value.c_str (), "%hhu,%hhu,%hhu,%hhu", &input_pins[0], &input_pins[1], &input_pins[2], &input_pins[3]);
 RegisterRemoteControl ();
}

void
cpart_step::RegisterRemoteControl(void)
{
 for (int i = 0; i < outputc; i++)
  {
   switch (output[i].id)
    {
    case O_ROT:
     output[i].status = (void *) &angle;
     break;
    }
  }
}

void
cpart_step::ConfigurePropertiesWindow(CPWindow * WProp)
{
 lxString Items = Window5.GetPinsNames ();
 lxString spin;

 ((CCombo*) WProp->GetChildByName ("combo1"))->SetItems (Items);
 if (input_pins[0] == 0)
  ((CCombo*) WProp->GetChildByName ("combo1"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[0]);
   ((CCombo*) WProp->GetChildByName ("combo1"))->SetText (itoa (input_pins[0]) + "  " + spin);
  }

 ((CCombo*) WProp->GetChildByName ("combo2"))->SetItems (Items);
 if (input_pins[1] == 0)
  ((CCombo*) WProp->GetChildByName ("combo2"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[1]);
   ((CCombo*) WProp->GetChildByName ("combo2"))->SetText (itoa (input_pins[1]) + "  " + spin);
  }

 ((CCombo*) WProp->GetChildByName ("combo3"))->SetItems (Items);
 if (input_pins[2] == 0)
  ((CCombo*) WProp->GetChildByName ("combo3"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[2]);
   ((CCombo*) WProp->GetChildByName ("combo3"))->SetText (itoa (input_pins[2]) + "  " + spin);
  }

 ((CCombo*) WProp->GetChildByName ("combo4"))->SetItems (Items);
 if (input_pins[3] == 0)
  ((CCombo*) WProp->GetChildByName ("combo4"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[3]);
   ((CCombo*) WProp->GetChildByName ("combo4"))->SetText (itoa (input_pins[3]) + "  " + spin);
  }

 ((CButton*) WProp->GetChildByName ("button1"))->EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CPWindow5::PropButtonRelease;
 ((CButton*) WProp->GetChildByName ("button1"))->SetTag (1);

 ((CButton*) WProp->GetChildByName ("button2"))->EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CPWindow5::PropButtonRelease;
}

void
cpart_step::ReadPropertiesWindow(CPWindow * WProp)
{
 input_pins[0] = atoi (((CCombo*) WProp->GetChildByName ("combo1"))->GetText ());
 input_pins[1] = atoi (((CCombo*) WProp->GetChildByName ("combo2"))->GetText ());
 input_pins[2] = atoi (((CCombo*) WProp->GetChildByName ("combo3"))->GetText ());
 input_pins[3] = atoi (((CCombo*) WProp->GetChildByName ("combo4"))->GetText ());
 RegisterRemoteControl ();
}

part_init("Step motor", cpart_step, "Output");

