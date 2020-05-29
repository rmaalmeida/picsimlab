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

#ifndef PART_VCD_DUMP_AN_H
#define	PART_VCD_DUMP_AN_H

#include<lxrad.h>
#include"part.h"

class cpart_VCD_Dump_an:public part
{
   public:
      String GetName(void){return lxT("VCD Dump (Analogic)");};
      cpart_VCD_Dump_an(unsigned x, unsigned y);
      ~cpart_VCD_Dump_an(void);
      void Draw(void);
      void Process(void);
      String GetPictureFileName(void){return lxT("VCD_Dump.png");};
      String GetInputMapFile(void){return lxT("VCD_Dump_i.map");};
      String GetOutputMapFile(void){return lxT("VCD_Dump_o.map");};
      String GetPropertiesWindowFile(void){return lxT("VCD_Dump.lxrad");};
      void EvMouseButtonPress(uint button, uint x, uint y,uint state);
      void ConfigurePropertiesWindow(CPWindow *  wprop);
      void ReadPropertiesWindow(void);
      String WritePreferences(void);
      void ReadPreferences(String value);
      unsigned short get_in_id(char * name);
      unsigned short get_out_id(char * name);
     private:
      unsigned char input_pins[8];    
      float old_value_pins[8];      
      char   f_vcd_name[200];
      FILE * f_vcd;
      unsigned long vcd_count;
      unsigned char rec;
};


#endif	/* PART_VCD_DUMP_AN_H */

