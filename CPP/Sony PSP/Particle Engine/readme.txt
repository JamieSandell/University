PSPDev Environment for Win32  .:.  http://xorloser.com


:: Notes

DO NOT INSTALL INTO A DIRECTORY WITH SPACES IN THE DIRECTORY NAME!
this can result in problems when using the installed tools.

This installation does not include the required headers and libs to
build tools for the pc.


:: Overview

This is an installable version of the PSPDev compilers and associated tools.
It is based on the GCC v4.0.2 toolchain and patches as found in the
ps2dev.org svn repository.
There are toolchains for PSP as well as the PSPSDK libraries required to
access the various hardware on the psp.

I also added patches based on nervus' original gcc patch for the ps2 toolchain
which enabled error and warning output in the MS VS.NET format.
You can get the original ps2 toolchain patches here: http://nervus.org/

This installer was made using NSIS v2.16, the free installer by nullsoft,
makers of winamp. This can be found at http://nsis.sourceforge.net/


:: Cygwin1.dll

This installer sets up a 'standalone' PSPDev environment using compilers built
with cygwin. This means that the cygwin1.dll is needed in order to run the
executable files in this package. If a different version of this dll currently
exists on your computer then it may cause conflicts. If you get error messages
when trying to use these tools i suggest doing a search of your disks to find
all other versions of the cygwin1.dll and either remove them from your path,
rename them to cygwin1.dll.bak (in case you need them in the future) or just
delete them.

NOTE: cygwin compiled executables that use older versions of this dll will not
work with a newer or different version of the dll. You must use the dll from
the same cygwin version as the executables were compiled with.


:: Installing

Run the installer to install and setup your PSPDev environment.
To use the dev environment you need to set up some environment variables,
the installer can do this for you in a number of ways. Either by setting
the environment variables for the current user, for all users, or by
preparing a batch file that allows you to set them temporarily when needed.
For users who don't use multiple dev environment, setting the environment
variables for either all users or the current user will mean that the dev
environment is always set up and ready to go. However for those users who
may have conflicts with other cygwin tools or dev environments, a batch
file would be the preferred choice.

If installing in windows 9x/ME there is no difference between the current
user and all users setting. Also a reboot is required after selecting either
of these options.

If installing in windows NT/2K/XP/2K3 there IS a difference between the current
user and all users setting, however a reboot is not required.

If you choose to use a batch file, you need to run the batch file from
your command prompt before using any of the pspdev tools. If you copy the
batch file to your path somewhere (such as your windows dir) then you can
call it from anywhere. If the batch file is in your path you can simply type:
'pspdev' at your command prompt and you are ready to go.

When using the batch file, your pspdev environment will only be valid in the
command prompt window that you typed 'pspdev' in. Once that window is closed
or another window is opened, you must type 'pspdev' again to setup your
temporary environment variables. You can safely use the dev tools in multiple
command prompt windows at once by typing 'pspdev' in each window before using
the tools.

All the above options set up the same environment variables, these are:
PSPDEV=InstallDir
PATH=%PATH%;%PSPDEV%/bin



Hopefully this will solve toolchain issues allowing you to start deving :)

for help with pspdev related problems, you may like to try the forums at
http://www.ps2dev.org or #pspdev irc channel on freenode.


enjoy :)


