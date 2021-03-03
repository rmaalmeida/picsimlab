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

#include"board_PQDB.h"

#define selectColorByValue(Value) {\
				if(Value){\
					draw -> Canvas.SetColor(205, 0,0); \
                }else{ \
                    draw -> Canvas.SetColor(205, 180, 180); \
                } \
            }

#define selectColorByPinValue(PIN_ID) selectColorByValue(pic.pins[PIN_ID].value)

/* outputs */
enum
{
 O_A1, O_B1, O_C1, O_D1, O_E1, O_F1, O_G1, O_P1,
 O_A2, O_B2, O_C2, O_D2, O_E2, O_F2, O_G2, O_P2,
 O_A3, O_B3, O_C3, O_D3, O_E3, O_F3, O_G3, O_P3,
 O_A4, O_B4, O_C4, O_D4, O_E4, O_F4, O_G4, O_P4,
 O_SOD0, O_SOD1, O_SOD2, O_SOD3, O_SOD4, O_SOD5, O_SOD6, O_SOD7,
 O_TC1, O_TC2, O_TC3, O_TC4, O_TC5, O_TC6, O_TC7, O_TC8,
 O_TC9, O_TC0, O_RST, O_POT, O_LPWR, O_LCD, O_PRG, O_RUN,
 O_RGB, O_KP1, O_KP2, O_PWM, O_DISP1, O_DISP2, O_DISP3, O_DISP4,
 O_SOEN, O_SOCLK, O_SODATA, O_LCDRS, O_LCDEN, O_SCL, O_SDA, O_TX,
 O_RX,
};

/*inputs*/

enum
{
 I_TC1, I_TC2, I_TC3, I_TC4, I_TC5, I_TC6, I_TC7, I_TC8, I_TC9, I_TC0,
 I_POT,
 I_RST, I_PWR,
};

cboard_PQDB::cboard_PQDB(void)
{

 Proc = "PIC18F4520";

 vtc = 0;
 vt = 0;

 pot = 100;

 active = 0;


 vPOT = 0;
 vLDR = 2.5;
 vLM = 2.5;

 vp2[0] = 2.5;
 vp2[1] = 2.5;
 temp[0] = 27.5;
 temp[1] = 27.5;
 ref = 0;

 rpmstp = 0; //(NSTEP*2)/100;
 rpmc = 0;

 d = 0;
 lcde = 0;
 sound_on = 0;

 lmrgb[0] = 0;
 lmrgb[1] = 0;
 lmrgb[2] = 0;

 sda = 0;
 
 srDATA = 0;
 srCLK = 0;
 srLAT = 0;

 lcd_init (& lcd, 16, 2);
 rtc2_init (& rtc2);
 io_74xx595_init (&shiftReg);

 ReadMaps ();

 buzzer.Init ();

 //gauge1
 /*  gauge1 = new CGauge();
  gauge1 -> SetFOwner( & Window1);
  gauge1 -> SetName(lxT("gauge1_p4"));
  gauge1 -> SetX(13);
  gauge1 -> SetY(302 + 20);
  gauge1 -> SetWidth(140);
  gauge1 -> SetHeight(20);
  gauge1 -> SetEnable(1);
  gauge1 -> SetVisible(1);
  gauge1 -> SetRange(100);
  gauge1 -> SetValue(0);
  gauge1 -> SetType(4); */
 //Window1.CreateChild(gauge1);
 /* gauge2
 gauge2 = new CGauge();
 gauge2 -> SetFOwner( & Window1);
 gauge2 -> SetName(lxT("gauge2_p4"));
 gauge2 -> SetX(12);
 gauge2 -> SetY(250 + 20);
 gauge2 -> SetWidth(140);
 gauge2 -> SetHeight(20);
 gauge2 -> SetEnable(1);
 gauge2 -> SetVisible(1);
 gauge2 -> SetRange(100);
 gauge2 -> SetValue(0);
 gauge2 -> SetType(4);
 Window1.CreateChild(gauge2); */
 //label3
 /* label3 = new CLabel();
 label3 -> SetFOwner( & Window1);
 label3 -> SetName(lxT("label3_p4"));
 label3 -> SetX(12);
 label3 -> SetY(226 + 20);
 label3 -> SetWidth(60);
 label3 -> SetHeight(20);
 label3 -> SetEnable(1);
 label3 -> SetVisible(1);
 label3 -> SetText(lxT("Heater"));
 label3 -> SetAlign(1);
 Window1.CreateChild(label3); */
 //label4
 /* label4 = new CLabel();
 label4 -> SetFOwner( & Window1);
 label4 -> SetName(lxT("label4_p4"));
 label4 -> SetX(13);
 label4 -> SetY(277 + 20);
 label4 -> SetWidth(60);
 label4 -> SetHeight(20);
 label4 -> SetEnable(1);
 label4 -> SetVisible(1);
 label4 -> SetText(lxT("Cooler"));
 label4 -> SetAlign(1);
 Window1.CreateChild(label4); */
 //label5
 /* label5 = new CLabel();
 label5 -> SetFOwner( & Window1);
 label5 -> SetName(lxT("label5_p4"));
 label5 -> SetX(13);
 label5 -> SetY(332 + 20);
 label5 -> SetWidth(120);
 label5 -> SetHeight(24);
 label5 -> SetEnable(1);
 label5 -> SetVisible(1);
 label5 -> SetText(lxT("Temp: 00.0°C"));
 label5 -> SetAlign(1);
 Window1.CreateChild(label5); */
 //label6
 /* label6 = new CLabel();
 label6 -> SetFOwner( & Window1);
 label6 -> SetName(lxT("label6_p4"));
 label6 -> SetX(13);
 label6 -> SetY(54 + 20);
 label6 -> SetWidth(120);
 label6 -> SetHeight(24);
 label6 -> SetEnable(1);
 label6 -> SetVisible(1);
 label6 -> SetText(lxT("LCD"));
 label6 -> SetAlign(1);
 Window1.CreateChild(label6); */
 //combo1
 /* combo1 = new CCombo();
 combo1 -> SetFOwner( & Window1);
 combo1 -> SetName(lxT("combo1_p4"));
 combo1 -> SetX(13);
 combo1 -> SetY(78 + 20);
 combo1 -> SetWidth(130);
 combo1 -> SetHeight(24);
 combo1 -> SetEnable(1);
 combo1 -> SetVisible(1);
 combo1 -> SetText(lxT("hd44780 16x2"));
 combo1 -> SetItems(lxT("hd44780 16x2,hd44780 16x4,"));
 combo1 -> SetTag(3);
 combo1 -> EvOnComboChange = EVONCOMBOCHANGE & CPWindow1::board_Event;
 Window1.CreateChild(combo1); */

}

cboard_PQDB::~cboard_PQDB(void)
{
 buzzer.BeepStop ();
 buzzer.End ();


 rtc2_end (& rtc2);

 /*  Window1.DestroyChild(gauge1);
  Window1.DestroyChild(gauge2);
  Window1.DestroyChild(label3);
  Window1.DestroyChild(label4);
  Window1.DestroyChild(label5);
  Window1.DestroyChild(label6);
  Window1.DestroyChild(combo1); */

}

void
cboard_PQDB::Draw(CDraw * draw, double scale)
{
 int i;
 draw -> Canvas.Init (scale, scale);

 lcd_blink (& lcd);

 //lab4 draw 
 for (i = 0; i < outputc; i++)
  {
   if (!output[i].r)
    {

     draw -> Canvas.SetFgColor (30, 0, 0);
     //seven segments display
     switch (output[i].id)
      {
      case O_A1:
      case O_B1:
      case O_C1:
      case O_D1:
      case O_E1:
      case O_F1:
      case O_G1:
      case O_P1:
      case O_A2:
      case O_B2:
      case O_C2:
      case O_D2:
      case O_E2:
      case O_F2:
      case O_G2:
      case O_P2:
      case O_A3:
      case O_B3:
      case O_C3:
      case O_D3:
      case O_E3:
      case O_F3:
      case O_G3:
      case O_P3:
      case O_A4:
      case O_B4:
      case O_C4:
      case O_D4:
      case O_E4:
      case O_F4:
      case O_G4:
      case O_P4:
       draw -> Canvas.SetColor (255, 255 - lm7seg[output[i].id], 255 - lm7seg[output[i].id]);
       break;
      case O_LCD:
       draw -> Canvas.SetColor (0, 90 * Window1.Get_mcupwr () + 40, 0);
       break;
      case O_RST:
       draw -> Canvas.SetColor (100, 100, 100);
       draw -> Canvas.Rectangle (1, output[i].x1 + 1, output[i].y1 + 1, output[i].x2 - output[i].x1 - 1, output[i].y2 - output[i].y1 - 1);
       if (p_RST)
        {
         draw -> Canvas.SetColor (15, 15, 15);
        }
       else
        {
         draw -> Canvas.SetColor (55, 55, 55);
        }
       break;

      case O_SOEN:
       selectColorByPinValue (SO_EN_PIN);
       break;
      case O_SOCLK:
       selectColorByPinValue (SO_CLK_PIN);
       break;
      case O_SODATA:
       selectColorByPinValue (SO_DATA_PIN);
       break;
      case O_DISP1:
       selectColorByPinValue (DISP_1_PIN);
       break;
      case O_DISP2:
       selectColorByPinValue (DISP_2_PIN);
       break;
      case O_DISP3:
       selectColorByPinValue (DISP_3_PIN);
       break;
      case O_DISP4:
       selectColorByPinValue (DISP_4_PIN);
       break;
      case O_KP1:
       selectColorByPinValue (KEYPAD_1_PIN);
       break;
      case O_KP2:
       selectColorByPinValue (KEYPAD_2_PIN);
       break;
      case O_PWM:
       selectColorByPinValue (PWM_PIN);
       break;
      case O_LCDRS:
       selectColorByPinValue (LCD_RS_PIN);
       break;
      case O_LCDEN:
       selectColorByPinValue (LCD_EN_PIN);
       break;
      case O_SCL:
       selectColorByPinValue (SCL_PIN);
       break;
      case O_SDA:
       //use sda instead pinValue becouse switching input/output
       selectColorByValue (sda);
       break;
      case O_TX:
       selectColorByPinValue (TX_PIN);
       break;
      case O_RX:
       selectColorByPinValue (RX_PIN);
       break;
      case O_SOD0:
      case O_SOD1:
      case O_SOD2:
      case O_SOD3:
      case O_SOD4:
      case O_SOD5:
      case O_SOD6:
      case O_SOD7:
       selectColorByValue ((shiftReg.out & (1 << (output[i].id - O_SOD0))));
       break;
      case O_TC1:
      case O_TC2:
      case O_TC3:
      case O_TC4:
      case O_TC5:
      case O_TC6:
      case O_TC7:
      case O_TC8:
      case O_TC9:
      case O_TC0:
       draw -> Canvas.SetColor (100, 100, 100);
       draw -> Canvas.Rectangle (1, output[i].x1 + 1, output[i].y1 + 1, output[i].x2 - output[i].x1 - 1, output[i].y2 - output[i].y1 - 1);
       if (p_KEY[output[i].id - O_TC1])
        {
         draw->Canvas.SetColor (80, 80, 80);
        }
       else
        {
         draw->Canvas.SetColor (15, 15, 15);
        }
       break;
      default:
       break;
      }

     if ((output[i].id >= O_TC1) && (output[i].id <= O_TC0))
      {
       draw -> Canvas.Circle (1, output[i].cx, output[i].cy, 9);
      }
     else if (output[i].id == O_RST)
      {
       draw -> Canvas.Circle (1, output[i].cx, output[i].cy, 9);
      }
     else if (output[i].id == O_POT)
      {
       draw -> Canvas.SetColor (00, 17, 117);
       draw -> Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2 - output[i].x1, output[i].y2 - output[i].y1);

       draw -> Canvas.SetColor (250, 250, 250);
       draw -> Canvas.Circle (1, output[i].cx, output[i].cy, 38);

       draw -> Canvas.SetColor (50, 50, 50);
       int x = -30 * sin ((5.585 * (pot / 200.0)) + 0.349);
       int y = 30 * cos ((5.585 * (pot / 200.0)) + 0.349);
       draw -> Canvas.Circle (1, output[i].cx + x, output[i].cy + y, 4);

      }
     else if ((output[i].id != O_LCD))
      {
       draw -> Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2 - output[i].x1, output[i].y2 - output[i].y1);
      }

     //draw lcd text 
     if (output[i].id == O_LCD)
      {
       lcd_draw (&lcd, &draw->Canvas, output[i].x1, output[i].y1, output[i].x2 - output[i].x1, output[i].y2 - output[i].y1, Window1.Get_mcupwr ());
      }

    }
   else
    {
     draw -> Canvas.SetFgColor (0, 0, 0);
     draw -> Canvas.SetColor (25, 15, 15);

     if (output[i].id == O_LPWR)
      {
       draw -> Canvas.SetColor (0, 255 * Window1.Get_mcupwr (), 0);
      }
     draw -> Canvas.Circle (1, output[i].x1, output[i].y1, output[i].r);

     if (output[i].id == O_RGB)
      {
       draw -> Canvas.SetColor (lmrgb[0], lmrgb[1], lmrgb[2]);
       draw -> Canvas.Circle (1, output[i].cx, output[i].cy, 19);
      }
    }

  }
 rtc2_update (& rtc2);
 //end draw

 draw -> Canvas.End ();
 draw -> Update ();

 if (((0.5 * (pic.pins[PWM_PIN].oavalue - 55)) > 10) && (Window1.Get_mcupwr ()))
  {
   if (!sound_on)
    {
     buzzer.BeepStart ();
     sound_on = 1;
    }
  }
 else
  {
   buzzer.BeepStop ();
   sound_on = 0;
  }


 //tensão p2
 vPOT = (5.0 * pot / 199);
 vLDR = (5.0 * pot / 199);
 vLM = (5.0 * pot / 199);


 //pic_set_apin(4, 0);

 //referencia
 //pic_set_apin(pic,5,2.5);

}

void
cboard_PQDB::Run_CPU(void)
{
 int i;
 int j;
 const picpin * pins;

 unsigned int alm[40]; //valor médio dos pinos de IO

 float alm7seg[32]; //luminosidade media display 7 seg

 int JUMPSTEPS = Window1.GetJUMPSTEPS ();
 long int NSTEP = Window1.GetNSTEP () / pic.PINCOUNT;

 if (use_spare) Window5.PreProcess ();

 memset (alm7seg, 0, 32 * sizeof (unsigned int));

 memset (alm, 0, 40 * sizeof (unsigned int));

 pins = pic.pins;

 j = JUMPSTEPS;

 if (Window1.Get_mcupwr ())
  {
   for (i = 0; i < Window1.GetNSTEP (); i++)
    {
     if (j >= JUMPSTEPS)
      {
       pic_set_pin (pic.mclr, p_RST);

       //keyboard 
       //D3-7 do shiftReg
       //0-9: UDLRS sABXY
       if (pins[KEYPAD_1_PIN].dir)
        {
         if ((p_KEY[0] && (shiftReg.out & SRD3)) ||
             (p_KEY[1] && (shiftReg.out & SRD4)) ||
             (p_KEY[2] && (shiftReg.out & SRD5)) ||
             (p_KEY[3] && (shiftReg.out & SRD6)) ||
             (p_KEY[4] && (shiftReg.out & SRD7)))
          {
           pic_set_pin (KEYPAD_1_PIN + 1, 1);
          }
         else
          {
           pic_set_pin (KEYPAD_1_PIN + 1, 0);
          }
        }
       if (pins[KEYPAD_2_PIN].dir)
        {
         if ((p_KEY[5] && (shiftReg.out & SRD3)) ||
             (p_KEY[6] && (shiftReg.out & SRD4)) ||
             (p_KEY[7] && (shiftReg.out & SRD5)) ||
             (p_KEY[8] && (shiftReg.out & SRD6)) ||
             (p_KEY[9] && (shiftReg.out & SRD7)))
          {
           pic_set_pin (KEYPAD_2_PIN + 1, 1);
          }
         else
          {
           pic_set_pin (KEYPAD_2_PIN + 1, 0);
          }
        }

      }

     if (!mplabxd_testbp ()) pic_step ();

     if (use_oscope) Window4.SetSample ();
     if (use_spare) Window5.Process ();

     //increment mean value counter if pin is high
     alm[i % pic.PINCOUNT] += pins[i % pic.PINCOUNT].value;

     if (j >= JUMPSTEPS)
      {
       //contabilizando a média do 7 segmentos
       for (int iDisp = DISP_1_PIN; iDisp <= DISP_4_PIN; iDisp++)
        {
         if (pins[iDisp].value && !pins[iDisp].dir)
          {
           for (int iSeg = 0; iSeg < 8; iSeg++)
            {
             if (shiftReg.out & (1 << iSeg))
              {
               if (lm7seg[(iDisp - DISP_1_PIN)*8 + iSeg] < 254)
                {
                 lm7seg[(iDisp - DISP_1_PIN)*8 + iSeg]++;
                }

              }
             else
              {
               lm7seg[(iDisp - DISP_1_PIN)*8 + iSeg] *= 0.8;
              }
            }
          }
        }
       //contabilizando luminosidade do RGB
       if (pins[LED_RED_PIN].value)
        {
         lmrgb[0]++;
         if (lmrgb[0] > 255) lmrgb[0] = 255;
        }
       else
        {
         lmrgb[0]--;
         if (lmrgb[0] < 0)
          {
           lmrgb[0] = 0;
          }
        }
       if (pins[LED_GREEN_PIN].value)
        {
         lmrgb[1]++;
         if (lmrgb[1] > 255) lmrgb[1] = 255;
        }
       else
        {
         lmrgb[1]--;
         if (lmrgb[1] < 0)
          {
           lmrgb[1] = 0;
          }
        }
       if (pins[LED_BLUE_PIN].value)
        {
         lmrgb[2]++;
         if (lmrgb[2] > 255) lmrgb[2] = 255;
        }
       else
        {
         lmrgb[2]--;
         if (lmrgb[2] < 0)
          {
           lmrgb[2] = 0;
          }
        }

       alm[32] = 0;

       // potenciometro p1 e p2
       pic_set_apin (POT_PIN + 1, vPOT); //pot
       pic_set_apin (LDR_PIN + 1, vLDR); //ldr
       pic_set_apin (LM_PIN + 1, vLM); //temp

       j = -1;
      }
     j++;

     //lcd display code
     if ((!pins[LCD_EN_PIN].dir) && (!pins[LCD_EN_PIN].value))
      {
       if (!lcde)
        {
         d = (shiftReg.out & 0x0f) << 4;

         if ((!pins[LCD_RS_PIN].dir) && (!pins[LCD_RS_PIN].value))
          {
           lcd_cmd (&lcd, d);
          }
         else if ((!pins[LCD_RS_PIN].dir) && (pins[LCD_RS_PIN].value))
          {
           lcd_data (&lcd, d);
          }
         lcde = 1;
        }
      }
     else
      {
       lcde = 0;
      }
     //end display code     


     //ds1307 over i2c code
     if (pins[SDA_PIN].dir)
      {
       sda = 1;
      }
     else
      {
       sda = pins[SDA_PIN].value;
      }
     if (pins[SCL_PIN].dir)
      {
       sck = 1;
       pic_set_pin (SCL_PIN + 1, 1);
      }
     else
      {
       sck = pins[SCL_PIN].value;
      }
     pic_set_pin (SDA_PIN + 1, rtc2_io (& rtc2, sck, sda));


     //74hc595 code
     if (pins[SO_DATA_PIN].dir == 0)
      {
       srDATA = pins[SO_DATA_PIN].value;
      }
     if (pins[SO_CLK_PIN].dir == 0)
      {
       srCLK = pins[SO_CLK_PIN].value;
      }
     if (pins[SO_EN_PIN].dir == 0)
      {
       srLAT = pins[SO_EN_PIN].value;
      }
     io_74xx595_io (&shiftReg, srDATA, srCLK, srLAT, 1);
    }

   //fim STEP

   alm[23] = 0; //aquecedor
   alm[16] = 0; //ventilador


   for (i = 0; i < pic.PINCOUNT; i++)
    {
     if (pic.pins[i].port == P_VDD)
      {
       pic.pins[i].oavalue = 255;
      }
     else
      {
       pic.pins[i].oavalue = (int) (((200.0 * alm[i]) / NSTEP) + 55);
      }
    }

   if (use_spare) Window5.PostProcess ();
  }

}

void
cboard_PQDB::Reset(void)
{

 pic_reset (1);

 lcd_rst (& lcd);
 rtc2_rst (& rtc2);
 io_74xx595_rst (&shiftReg);

 p_KEY[0] = 0;
 p_KEY[1] = 0;
 p_KEY[2] = 0;
 p_KEY[3] = 0;
 p_KEY[4] = 0;
 p_KEY[5] = 0;
 p_KEY[6] = 0;
 p_KEY[7] = 0;
 p_KEY[8] = 0;
 p_KEY[9] = 0;


#ifndef _WIN_
 if (pic.serial[0].serialfd > 0)
#else
 if (pic.serial[0].serialfd != INVALID_HANDLE_VALUE)
#endif
  Window1.statusbar1.SetField (2, lxT ("Serial: ") + lxString::FromAscii (SERIALDEVICE) + lxT (":") + itoa (pic.serial[0].serialbaud) + lxT ("(") + lxString ().Format ("%4.1f", fabs ((100.0 * pic.serial[0].serialexbaud - 100.0 * pic.serial[0].serialbaud) / pic.serial[0].serialexbaud)) + lxT ("%)"));
 else
  Window1.statusbar1.SetField (2, lxT ("Serial: ") + lxString::FromAscii (SERIALDEVICE) + lxT (" (ERROR)"));

 for (int i = 0; i < 32; i++)
  {
   lm7seg[i] = 0;
  }

 if (use_spare) Window5.Reset ();

 RegisterRemoteControl ();
}

void
cboard_PQDB::RegisterRemoteControl(void)
{
 for (int i = 0; i < inputc; i++)
  {
   switch (input[i].id)
    {
    case I_TC1:
     input[i].status = &p_KEY[0];
     break;
    case I_TC2:
     input[i].status = &p_KEY[1];
     break;
    case I_TC3:
     input[i].status = &p_KEY[2];
     break;
    case I_TC4:
     input[i].status = &p_KEY[3];
     break;
    case I_TC5:
     input[i].status = &p_KEY[4];
     break;
    case I_TC6:
     input[i].status = &p_KEY[5];
     break;
    case I_TC7:
     input[i].status = &p_KEY[6];
     break;
    case I_TC8:
     input[i].status = &p_KEY[7];
     break;
    case I_TC9:
     input[i].status = &p_KEY[8];
     break;
    case I_TC0:
     input[i].status = &p_KEY[9];
     break;
    case I_POT:
     input[i].status = &pot;
     break;
    }
  }

 for (int i = 0; i < outputc; i++)
  {
   switch (output[i].id)
    {

    case O_LCD:
     output[i].status = &lcd;
     break;
    case O_A1:
    case O_B1:
    case O_C1:
    case O_D1:
    case O_E1:
    case O_F1:
    case O_G1:
    case O_P1:
    case O_A2:
    case O_B2:
    case O_C2:
    case O_D2:
    case O_E2:
    case O_F2:
    case O_G2:
    case O_P2:
    case O_A3:
    case O_B3:
    case O_C3:
    case O_D3:
    case O_E3:
    case O_F3:
    case O_G3:
    case O_P3:
    case O_A4:
    case O_B4:
    case O_C4:
    case O_D4:
    case O_E4:
    case O_F4:
    case O_G4:
    case O_P4:
     output[i].status = &lm7seg[output[i].id];
     break;
    }
  }
}

void
cboard_PQDB::EvMouseMove(uint button, uint x, uint y, uint state)
{
 int i;

 for (i = 0; i < inputc; i++)
  {
   switch (input[i].id)
    {
    case I_POT:
     if (((input[i].x1 <= x) && (input[i].x2 >= x)) && ((input[i].y1 <= y) && (input[i].y2 >= y)))
      {
       if (active)
        {
         pot = CalcAngle (i, x, y);
        }
      }
     break;
    }
  }
}

void
cboard_PQDB::EvMouseButtonPress(uint button, uint x, uint y, uint state)
{

 int i;

 for (i = 0; i < inputc; i++)
  {
   if ((input[i].x1 <= x) &&
       (input[i].x2 >= x) &&
       (input[i].y1 <= y) &&
       (input[i].y2 >= y))
    {

     switch (input[i].id)
      {

      case I_PWR:
       {
        if (Window1.Get_mcupwr ())
         {
          Window1.Set_mcurun (0);
          Window1.Set_mcupwr (0);
          Reset ();

          Window1.statusbar1.SetField (0, lxT ("Stoped"));
         }
        else
         {
          Window1.Set_mcupwr (1);
          Window1.Set_mcurun (1);
          Reset ();

          Window1.statusbar1.SetField (0, lxT ("Running..."));
         }
       }
       break;

      case I_RST:
       {
        if (Window1.Get_mcupwr () && pic_reset (-1))
         {
          Window1.Set_mcupwr (0);
          Window1.Set_mcurst (1);
         }
        p_RST = 0;
       }
       break;

      case I_TC1:
       {
        p_KEY[0] = 1;
       }
       break;
      case I_TC2:
       {
        p_KEY[1] = 1;
       }
       break;
      case I_TC3:
       {
        p_KEY[2] = 1;
       }
       break;

      case I_TC4:
       {
        p_KEY[3] = 1;
       }
       break;
      case I_TC5:
       {
        p_KEY[4] = 1;
       }
       break;
      case I_TC6:
       {
        p_KEY[5] = 1;
       }
       break;

      case I_TC7:
       {
        p_KEY[6] = 1;
       }
       break;
      case I_TC8:
       {
        p_KEY[7] = 1;
       }
       break;
      case I_TC9:
       {
        p_KEY[8] = 1;
       }
       break;

      case I_TC0:
       {
        p_KEY[9] = 1;
       }
       break;
      case I_POT:
       {
        active = 1;
        pot = CalcAngle (i, x, y);
       }
       break;
      }
    }
  }
}

void
cboard_PQDB::EvMouseButtonRelease(uint button, uint x, uint y, uint state)
{
 int i;

 for (i = 0; i < inputc; i++)
  {
   if (((input[i].x1 <= x) && (input[i].x2 >= x)) && ((input[i].y1 <= y) && (input[i].y2 >= y)))
    {
     switch (input[i].id)
      {
      case I_RST:
       {
        if (Window1.Get_mcurst ())
         {
          Window1.Set_mcupwr (1);
          Window1.Set_mcurst (0);

          if (pic_reset (-1))
           {
            Reset ();
           }
         }
        p_RST = 1;
       }
       break;

      case I_TC1:
       {
        p_KEY[0] = 0;
       }
       break;
      case I_TC2:
       {
        p_KEY[1] = 0;
       }
       break;
      case I_TC3:
       {
        p_KEY[2] = 0;
       }
       break;

      case I_TC4:
       {
        p_KEY[3] = 0;
       }
       break;
      case I_TC5:
       {
        p_KEY[4] = 0;
       }
       break;
      case I_TC6:
       {
        p_KEY[5] = 0;
       }
       break;

      case I_TC7:
       {
        p_KEY[6] = 0;
       }
       break;
      case I_TC8:
       {
        p_KEY[7] = 0;
       }
       break;
      case I_TC9:
       {
        p_KEY[8] = 0;
       }
       break;

      case I_TC0:
       {
        p_KEY[9] = 0;
       }
       break;
      case I_POT:
       {
        active = 0;
       }
       break;
      }
    }
  }

}

void
cboard_PQDB::EvKeyPress(uint key, uint mask)
{
 if (key == '1')
  {
   p_KEY[0] = 1;
  }
 if (key == '2')
  {
   p_KEY[1] = 1;
  }
 if (key == '3')
  {
   p_KEY[2] = 1;
  }
 if (key == '4')
  {
   p_KEY[3] = 1;
  }
 if (key == '5')
  {
   p_KEY[4] = 1;
  }
 if (key == '6')
  {
   p_KEY[5] = 1;
  }
 if (key == '7')
  {
   p_KEY[6] = 1;
  }
 if (key == '8')
  {
   p_KEY[7] = 1;
  }
 if (key == '9')
  {
   p_KEY[8] = 1;
  }
 if (key == '0')
  {
   p_KEY[9] = 1;
  }
}

void
cboard_PQDB::EvKeyRelease(uint key, uint mask)
{
 if (key == '1')
  {
   p_KEY[0] = 0;
  }
 if (key == '2')
  {
   p_KEY[1] = 0;
  }
 if (key == '3')
  {
   p_KEY[2] = 0;
  }
 if (key == '4')
  {
   p_KEY[3] = 0;
  }
 if (key == '5')
  {
   p_KEY[4] = 0;
  }
 if (key == '6')
  {
   p_KEY[5] = 0;
  }
 if (key == '7')
  {
   p_KEY[6] = 0;
  }
 if (key == '8')
  {
   p_KEY[7] = 0;
  }
 if (key == '9')
  {
   p_KEY[8] = 0;
  }
 if (key == '0')
  {
   p_KEY[9] = 0;
  }
}

void
cboard_PQDB::EvOnShow(void)
{
 lcd.update = 1;
}

unsigned short
cboard_PQDB::get_in_id(char * name)
{
 if (strcmp (name, "PB_RST") == 0) return I_RST;
 if (strcmp (name, "SW_PWR") == 0) return I_PWR;

 if (strcmp (name, "PB_SW1") == 0) return I_TC1;
 if (strcmp (name, "PB_SW2") == 0) return I_TC2;
 if (strcmp (name, "PB_SW3") == 0) return I_TC3;
 if (strcmp (name, "PB_SW4") == 0) return I_TC4;
 if (strcmp (name, "PB_SW5") == 0) return I_TC5;
 if (strcmp (name, "PB_SW6") == 0) return I_TC6;
 if (strcmp (name, "PB_SW7") == 0) return I_TC7;
 if (strcmp (name, "PB_SW8") == 0) return I_TC8;
 if (strcmp (name, "PB_SW9") == 0) return I_TC9;
 if (strcmp (name, "PB_SW10") == 0) return I_TC0;

 if (strcmp (name, "PO_1") == 0) return I_POT;

 printf ("Erro input '%s' don't have a valid id! \n", name);
 return -1;
}

unsigned short
cboard_PQDB::get_out_id(char * name)
{

 if (strcmp (name, "PB_RST") == 0) return O_RST;


 if (strcmp (name, "DISP1") == 0) return O_DISP1;
 if (strcmp (name, "DISP2") == 0) return O_DISP2;
 if (strcmp (name, "DISP3") == 0) return O_DISP3;
 if (strcmp (name, "DISP4") == 0) return O_DISP4;


 if (strcmp (name, "KP1") == 0) return O_KP1;
 if (strcmp (name, "KP2") == 0) return O_KP2;

 if (strcmp (name, "PWM") == 0) return O_PWM;

 if (strcmp (name, "LCD_RS") == 0) return O_LCDRS;
 if (strcmp (name, "LCD_EN") == 0) return O_LCDEN;

 if (strcmp (name, "SCL") == 0) return O_SCL;
 if (strcmp (name, "SDA") == 0) return O_SDA;

 if (strcmp (name, "TX") == 0) return O_TX;
 if (strcmp (name, "RX") == 0) return O_RX;




 if (strcmp (name, "SO_D0") == 0) return O_SOD0;
 if (strcmp (name, "SO_D1") == 0) return O_SOD1;
 if (strcmp (name, "SO_D2") == 0) return O_SOD2;
 if (strcmp (name, "SO_D3") == 0) return O_SOD3;
 if (strcmp (name, "SO_D4") == 0) return O_SOD4;
 if (strcmp (name, "SO_D5") == 0) return O_SOD5;
 if (strcmp (name, "SO_D6") == 0) return O_SOD6;
 if (strcmp (name, "SO_D7") == 0) return O_SOD7;

 if (strcmp (name, "SO_DATA") == 0) return O_SODATA;
 if (strcmp (name, "SO_CLK") == 0) return O_SOCLK;
 if (strcmp (name, "SO_EN") == 0) return O_SOEN;


 if (strcmp (name, "LD_PRG") == 0) return O_PRG;
 if (strcmp (name, "LD_RUN") == 0) return O_RUN;

 if (strcmp (name, "SS_A1") == 0) return O_A1;
 if (strcmp (name, "SS_B1") == 0) return O_B1;
 if (strcmp (name, "SS_C1") == 0) return O_C1;
 if (strcmp (name, "SS_D1") == 0) return O_D1;
 if (strcmp (name, "SS_E1") == 0) return O_E1;
 if (strcmp (name, "SS_F1") == 0) return O_F1;
 if (strcmp (name, "SS_G1") == 0) return O_G1;
 if (strcmp (name, "SS_P1") == 0) return O_P1;

 if (strcmp (name, "SS_A2") == 0) return O_A2;
 if (strcmp (name, "SS_B2") == 0) return O_B2;
 if (strcmp (name, "SS_C2") == 0) return O_C2;
 if (strcmp (name, "SS_D2") == 0) return O_D2;
 if (strcmp (name, "SS_E2") == 0) return O_E2;
 if (strcmp (name, "SS_F2") == 0) return O_F2;
 if (strcmp (name, "SS_G2") == 0) return O_G2;
 if (strcmp (name, "SS_P2") == 0) return O_P2;

 if (strcmp (name, "LD_PWR") == 0) return O_LPWR;
 if (strcmp (name, "DS_LCD") == 0) return O_LCD;

 if (strcmp (name, "SS_A3") == 0) return O_A3;
 if (strcmp (name, "SS_B3") == 0) return O_B3;
 if (strcmp (name, "SS_C3") == 0) return O_C3;
 if (strcmp (name, "SS_D3") == 0) return O_D3;
 if (strcmp (name, "SS_E3") == 0) return O_E3;
 if (strcmp (name, "SS_F3") == 0) return O_F3;
 if (strcmp (name, "SS_G3") == 0) return O_G3;
 if (strcmp (name, "SS_P3") == 0) return O_P3;

 if (strcmp (name, "SS_A4") == 0) return O_A4;
 if (strcmp (name, "SS_B4") == 0) return O_B4;
 if (strcmp (name, "SS_C4") == 0) return O_C4;
 if (strcmp (name, "SS_D4") == 0) return O_D4;
 if (strcmp (name, "SS_E4") == 0) return O_E4;
 if (strcmp (name, "SS_F4") == 0) return O_F4;
 if (strcmp (name, "SS_G4") == 0) return O_G4;
 if (strcmp (name, "SS_P4") == 0) return O_P4;

 if (strcmp (name, "KB_TC1") == 0) return O_TC1;
 if (strcmp (name, "KB_TC2") == 0) return O_TC2;
 if (strcmp (name, "KB_TC3") == 0) return O_TC3;
 if (strcmp (name, "KB_TC4") == 0) return O_TC4;
 if (strcmp (name, "KB_TC5") == 0) return O_TC5;
 if (strcmp (name, "KB_TC6") == 0) return O_TC6;
 if (strcmp (name, "KB_TC7") == 0) return O_TC7;
 if (strcmp (name, "KB_TC8") == 0) return O_TC8;
 if (strcmp (name, "KB_TC9") == 0) return O_TC9;
 if (strcmp (name, "KB_TC0") == 0) return O_TC0;

 if (strcmp (name, "PO_1") == 0) return O_POT;

 if (strcmp (name, "RGB") == 0) return O_RGB;

 printf ("Erro output '%s' don't have a valid id! \n", name);
 return 1;
}

void
cboard_PQDB::RefreshStatus(void)
{
 //    label5 -> SetText(lxT("Temp: ") + lxString().Format("%5.2f", temp[0]) + lxT("°C"));

#ifndef _WIN_
 if (pic.serial[0].serialfd > 0)
#else
 if (pic.serial[0].serialfd != INVALID_HANDLE_VALUE)
#endif
  Window1.statusbar1.SetField (2, lxT ("Serial: ") + lxString::FromAscii (SERIALDEVICE) + lxT (":") + itoa (pic.serial[0].serialbaud) + lxT ("(") + lxString ().Format ("%4.1f", fabs ((100.0 * pic.serial[0].serialexbaud - 100.0 * pic.serial[0].serialbaud) / pic.serial[0].serialexbaud)) + lxT ("%)"));
 else
  Window1.statusbar1.SetField (2, lxT ("Serial: ") + lxString::FromAscii (SERIALDEVICE) + lxT (" (ERROR)"));

}

void
cboard_PQDB::WritePreferences(void)
{
 Window1.saveprefs (lxT ("PQDB_proc"), Proc);
 Window1.saveprefs (lxT ("PQDB_clock"), lxString ().Format ("%2.1f", Window1.GetClock ()));
 Window1.saveprefs (lxT ("PQDB_pot"), lxString ().Format ("%i", pot));
}

void
cboard_PQDB::ReadPreferences(char * name, char * value)
{
 if (!strcmp (name, "PQDB_proc"))
  {
   Proc = value;
  }

 if (!strcmp (name, "PQDB_clock"))
  {
   Window1.SetClock (atof (value));
  }

 if (!strcmp (name, "PQDB_pot"))
  {
   pot = atoi (value);
  }
}

board_init("PQDB", cboard_PQDB);