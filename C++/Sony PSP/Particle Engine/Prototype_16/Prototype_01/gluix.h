
/*---------------------------------------------------------------------------*\

    gluix.h

    Copyright (c) 2001 Andre Bleau

    Revision:	January 4, 2001

    This program is freely distributable without licensing fees and is
    provided without guarantee or warrantee expressed or implied. This
    program is -not- in the public domain.

\*---------------------------------------------------------------------------*/

#ifndef GLUIX_H
#define GLUIX_H

// Current version
#define GLUIX_VERSION 1.01f

class GLUIX {
public:
	static float	get_version( void ) { return GLUIX_VERSION; };
};

// Constants for building DirState, ExtState and NameState
#define GLUIX_NONE				0
#define GLUIX_PANEL				1
#define GLUIX_LOCKED				2
#define GLUIX_NODEFCHECKBOX	4

// Constants for building Access
#define GLUIX_EXISTS			1
#define GLUIX_READABLE		2
#define GLUIX_WRITABLE		4
#define GLUIX_EXECUTABLE	8

// Constants for DefaultValueReset
#define GLUIX_NOAUTORESET	0
#define GLUIX_AUTORESET		1

// Constants for Type
#define GLUIX_REG 0	// Regular file
#define GLUIX_DIR	1	// Subdirectory

// Default widths of the edittext boxes
#define GLUIX_FSD_DIR_EDITTEXT_W  320
#define GLUIX_FSD_EXT_EDITTEXT_W   50
#define GLUIX_FSD_NAME_EDITTEXT_W 150

// Parts name for set_w, set_h, set_font...
enum GLUIX_FSD_Part {
	GLUIX_FSD_DIR_PANEL,
	GLUIX_FSD_DIR_EDITTEXT,
	GLUIX_FSD_DIR_BROWSE,
	GLUIX_FSD_DIR_CHECKBOX,
	GLUIX_FSD_EXT_PANEL,
	GLUIX_FSD_EXT_EDITTEXT,
	GLUIX_FSD_EXT_NUMBER,
	GLUIX_FSD_EXT_CHECKBOX,
	GLUIX_FSD_NAME_PANEL,
	GLUIX_FSD_NAME_EDITTEXT,
	GLUIX_FSD_NAME_BROWSE,
	GLUIX_FSD_NAME_CHECKBOX,
	GLUIX_FSD_OK,
	GLUIX_FSD_CANCEL,
	GLUIX_FSD_SUBMENU
};

class GLUIX_FileSelectionDialogIntern;

class GLUIX_FileSelectionDialog {
public:
	GLUIX_FileSelectionDialog(
		char *Title = NULL,
		void (*NewFileCB)(char *FileDir, char *FileName, char *FileExt) = NULL,
		int Flags = 0,
		int OrgX = -1,
		int OrgY = -1,
		int DirState  = GLUIX_PANEL,
		int ExtState  = GLUIX_PANEL,
		int NameState = GLUIX_PANEL,
		int Type = GLUIX_REG
	);
	~GLUIX_FileSelectionDialog();
	int	set_access(int Access);
   int 	set_bkgd_color(
      Byte Red, Byte Green, Byte Blue);
	int	set_default_dir(
		char  *FileDefaultDir,
		int 	DefaultValueReset = GLUIX_AUTORESET
	);
	int	set_default_ext(
		char  *FileDefaultExt,  
		int 	DefaultValueReset = GLUIX_AUTORESET
	);
	int	set_default_name(
		char *FileDefaultName, 
		int 	DefaultValueReset = GLUIX_AUTORESET
	);
	int	set_font(enum GLUIX_FSD_Part part, void *new_font);
	int	set_h(enum GLUIX_FSD_Part part, int new_size);
   int 	set_n_items_max(int new_n_items_max);
#ifdef DEPRECATED
   int	set_interface_text(
      char *DirPanelText,
      char *DirBrowseText,
      char *DirCheckboxText,
      char *ExtPanelText,
      char *ExtNumberText,
      char *ExtCheckboxText,
      char *NamePanelText,
      char *NameBrowseText,
      char *NameCheckboxText,
      char *OKText,
      char *CancelText,
      char *SubMenuText
   );
#endif
	int	set_text(enum GLUIX_FSD_Part part, char *new_text);
	int	set_w(enum GLUIX_FSD_Part part, int new_size);
	void	show(GLUI *gluiDisabled = NULL);
	
private:
	GLUIX_FileSelectionDialogIntern	*intern;
};
#endif
