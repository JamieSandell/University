[SCE CONFIDENTIAL DOCUMENT]
PSP(TM) Hardware Manual Release 1.0.0
                   Copyright (C) 2006 Sony Computer Entertainment Inc.
                                                   All Rights Reserved
                                                             Nov. 2006
======================================================================
This is a release of the PSP hardware manuals.

======================================================================
Package Structure
======================================================================
The document directory structure is as follows.

devkit/
 +-document
   +-hardware_manual
     |---Readme-English.txt
     |---Hardware-Restriction-English.pdf
     |---ALLEGREX
     |    |---ALLEGREX-Users_Manual-English.pdf
     |    |---ALLEGREX-Instruction_Manual-English.pdf
     |    |---FPU-Users_Manual-English.pdf
     |    |---FPU-Instruction_Manual-English.pdf
     |    +---Instruction_list
     |         +---ALLEGREX_FPU-Instruction_List-English.pdf
     |---Graphics_Engine
     |    |---Graphics_Engine-Users_Manual-English.pdf
     |    |---Graphics_Engine-Command_Reference_Manual-English.pdf
     |    +---Command_list
     |         +---Graphics_Engine-Command_List-English.pdf
     +---VFPU
          |---VFPU-Users_Manual-English.pdf
          |---VFPU-Instruction_Manual-English.pdf
          +---Instruction_list
               +---VFPU-Instruction_List-English.pdf

* Hardware-Restriction-English.pdf is a file that is included in the
Runtime Library package.

* It is recommended that the documents in this package be read using
Adobe Reader 6.0 or later.
The latest version of the Adobe Reader (formerly Adobe Acrobat Reader)
can be downloaded from Adobe's website.

======================================================================
Revisions
======================================================================
<FPU-Instruction_Manual>
- Deleted part of the description of mfc1.

----------------------------------------------------------------------
<Graphics_Engine-Users_Manual>
- Revised the description of the texture generation matrix for projection mapping as follows.
    Before revision: Mt00-Mt10
    After revision: Mt00-Mt11

- Revised the description of the texture compression index of Figure 13-4 in the Texture Compression Formats section.

- Revised the description of COLOR data of the DXT1 format in the Texture Compression Formats section as follows.
    Old text: BGR
    After revision: RGB

- Revised the description of the non-transparent mode of the DXT1 format in the Texture Compression Formats section as follows.
    Before revision: C2 = (2 x C2 + C1) / 3
    After revision: C2 = (2 x C0 + C1) / 3

- Revised the sequential order of bit data in the Texture Buffer section as follows.
    ＜DXT1＞
    Before revision: 63-32, 31-0
    After revision: 31-0, 63-32

    ＜DXT3＞
    Before revision: 127-96, 95-64, 63-32, 31-0
    After revision: 31-0, 63-32, 95-64, 127-96

    ＜DXT5＞
    Before revision: 127-96, 95-64, 63-32, 31-0
    After revision: 31-0, 63-32, 95-64, 127-96

- Added additional text to the description of Fast mode in the Texture Storage Modes section.

- Deleted the description of clear mode in the section on scissoring.

- Added additional text to the description of the 16-bit color format in the Masking section.
  Also changed the following.
    Before revision: 16-bit plain mask value
    After revision: 32-bit plain mask value

- Changed the description in the Buffer Configuration section as follows. 
    Before revision: Specify 512 bytes when setting the buffer width to 480 pixels.
    After revision: Specify 1024 bytes when setting the buffer width to 480 pixels.

- Deleted some information from the Memory Map section.

<Graphics_Engine-Command_Reference>
- Deleted the following command descriptions. 
    CMD_X2
    CMX_Y2
    CMD_Z2
    CMD_S2
    CMD_T2
    CMD_Q2
    CMD_RGB2
    CMD_AP2
    CMD_F2
    CMD_I2

- Revised the description of the FBP field of CMD_FBP to "The low-order 13 bits must be 0."

- Revised the description of the ZBP field of CMD_ZBP to "The low-order 13 bits must be 0."

- Revised the description of the EQU field of CMD_BLEND as follows.
    Before revision: 010 : Cs◎B-Cd◎A
    After revision: 010 : Cd◎B-Cs◎A

- Added additional text to the descriptions of the IR, IG, and IB fields of CMD_I2

<Graphics_Engine-Command_List>
- Deleted the following command descriptions from the Command List table.
    CMD_X2
    CMX_Y2
    CMD_Z2
    CMD_S2
    CMD_T2
    CMD_Q2
    CMD_RGB2
    CMD_AP2
    CMD_F2
    CMD_I2

----------------------------------------------------------------------
<VFPU-Instruction_List>
- Deleted the following instructions.
    vdiv.p
    vdiv.t
    vdiv.q

- Added the following instruction.
    vsync2

<VFPU-Users_Manual>
- Added errata for the case when a cache miss occurs due to lv.s and lv.q.

- Added information about the vsync2 instruction to the following sections.
    Errata when Write Buffer is Full 
    Prefixing Overview
    Prefix Stack

- Revised the example of register restrictions in the restrictions for the repeat instruction.

- Removed the vdiv.q instruction from the example in which overlapping exceptions that have occurred for restrictions on the repeat instruction can be recognized as exceptions.

- Added a section about reading VFPU control registers.

- Revised the description of ReadMatrix() and WriteMatrix() in the definitions of operations.

- Removed the following instructions from the list of execution cycles for each instruction. Also added the vsync2 instruction.
    vdiv.p
    vdiv.t
    vdiv.q

- Added the item "operand to encoding" to the encoding pattern of each format, and added information for "encoding to operand."

- Changed the table of correspondences between each instruction and prefixing as follows.
  <Changed vpfxs from Valid to Use Prohibited> for the following instructions:
    vbfy1.p
    vbfy1.q
    vbfy2.q
    vsrt1.q
    vsrt2.q
    vsrt3.q
    vsrt4.q

  <Changed vpfxt from No Effect to Use Prohibited> and
  <Changed vpfxd from Valid to Use Prohibited> for the following instructions.
    vcmovf.s
    vcmovf.p
    vcmovf.t
    vcmovf.q
    vcmovt.s
    vcmovt.p
    vcmovt.t
    vcmovt.q

- Deleted the following instructions from the table of prefixing for each instruction. Also added the vsync2 instruction.
    vdiv.p
    vdiv.t
    vdiv.q

<VFPU-Instruction_Manual>
- Added additional text to the precautions for sv.q (Store Quad Word to Write Buffer)

- Changed the descriptions of prefixing for the following instructions.
  <Changed vpfxs from Valid to Use Prohibited>
    vbfy1.p
    vbfy1.q
    vbfy2.q
    vsrt1.q
    vsrt2.q
    vsrt3.q
    vsrt4.q

  <Changed vpfxt from No Effect to Use Prohibited> and <Changed vpfxd from Valid to Use Prohibited> for the following instructions.
    vcmovf.s
    vcmovf.p
    vcmovf.t
    vcmovf.q
    vcmovt.s
    vcmovt.p
    vcmovt.t
    vcmovt.q

- Deleted the following instructions.
    vdiv.p
    vdiv.t
    vdiv.q

- Added supplementary text to the description of vflush.

- Added supplementary text to the precautions for the following instructions, and revised the descriptions of the operations.
    vmmul.p
    vmmul.t
    vmmul.q

- Added a description of the following instruction.
    vsync2

====================================================================
Usage permissions and restrictions
====================================================================
The usage permissions and restrictions pertaining to this software 
are described in the contract signed between your company and Sony 
Computer Entertainment.

====================================================================
Warnings about trademarks
====================================================================
"PSP" is a trademark of Sony Computer Entertainment.

Company names and product names which appear in these documents are 
trademarks or registered trademarks of the respective companies.
The (R) and (TM) marks may not explicitly appear.

====================================================================
Copyright
====================================================================
The copyright of this software belongs to Sony Computer 
Entertainment.
