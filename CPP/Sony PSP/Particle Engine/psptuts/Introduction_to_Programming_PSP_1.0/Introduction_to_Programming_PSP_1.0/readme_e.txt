[SCE CONFIDENTIAL DOCUMENT]

PSP(TM) Sample Code

Copyright (C) 2005 Sony Computer Entertainment Europe
All Rights Reserved.

Introduction to Programming the PSP - Code Samples version 1.0 

Date            Design      Log
----------------------------------------------------
2005-11-03      csawyer     initial implementation
----------------------------------------------------

Introduction:
----------------------------------------------------

These code samples are provided as an accompaniment to 
the document "Introduction to Programming the PSP". 
There are two directories for the code samples, one for 
the Emulator environment, and one for the Hardware Tool.

----------------------------------------------------------------------
Sample Directory Structure
----------------------------------------------------------------------
Introduction_to_Programming_the_PSP_1.0/
 |
 +---src/
     |
     +---emulator/			     
     |    |	
     |    +---hellotriangle/ 	2d rendering with text 		(Chapter 3)
     |    +---3dscene/		3d rendered scene			(Chapter 4)
     |    
     +---hwtool/
         |	
         +---hellotriangle/ 	2d rendering with text		(Chapter 3)
         +---3dscene/    	3d rendered scene			(Chapter 4)
	   +---vfpuscene/		3d rendered scene with VFPU	(Chapter 5)

Compilation
----------------------------------------------------
	% cd (directory)
	% make


