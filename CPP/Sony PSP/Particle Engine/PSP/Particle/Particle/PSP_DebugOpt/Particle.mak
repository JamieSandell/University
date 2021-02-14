####################################################
# PSP Makefile generated for GNU Make by ProDG VSI #
####################################################

.SILENT:

unexport MAKEFLAGS
unexport MFLAGS

OUTDIR = PSP_DebugOpt
INTDIR = PSP_DebugOpt

LIBS=\
	crt0_prx.o\
	PSPFramework.lib\
	PSPFramework.Maths.lib\
	PSPFramework.Utilities.lib\
	libfpu.a\
	libheap.a\
	libgu.a\
	libgum.a\
	libkernel.a\
	ctrl_stub.a\
	display_stub.a\
	ge_user_stub.a\
	kernel_bridge.o\

AS=pspsnc
AS_FLAGS=\
	-DSN_TARGET_PSP_PRX\
	-D_DEBUG\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework.Maths/PSP_DebugOpt"\
	-I"C:/SEED TFS/PSPDev Kit/PSPResource/lib"\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework.Utilities/PSP_DebugOpt"\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework/PSP_DebugOpt"\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework"\
	-I$(SCE_PSP_HW_ROOT)/include\
	-I.\
	-c\
	-Xmserrors\
	-g\

CC=pspsnc
CC_FLAGS=\
	-DSN_TARGET_PSP_PRX\
	-D_DEBUG\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework.Maths/PSP_DebugOpt"\
	-I"C:/SEED TFS/PSPDev Kit/PSPResource/lib"\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework.Utilities/PSP_DebugOpt"\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework/PSP_DebugOpt"\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework"\
	-I$(SCE_PSP_HW_ROOT)/include\
	-I.\
	-c\
	-Xmserrors\
	-MMD\
	-g\
	-O3\

CXX=pspsnc
CXX_FLAGS=\
	-DSN_TARGET_PSP_PRX\
	-D_DEBUG\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework.Maths/PSP_DebugOpt"\
	-I"C:/SEED TFS/PSPDev Kit/PSPResource/lib"\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework.Utilities/PSP_DebugOpt"\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework/PSP_DebugOpt"\
	-I"C:/SEED TFS/PSPDev Kit/PSPFramework"\
	-I$(SCE_PSP_HW_ROOT)/include\
	-I.\
	-c\
	-Xmserrors\
	-MMD\
	-g\
	-O3\

LCFILE = "C:/Program Files/SN Systems/PSP/lib/psp.ld"

LD=pspsnc
LD_FLAGS=\
	-L"F:/SEED TFS/PSPDev Kit/PSPResource/lib"\
	-L"F:/SEED TFS/PSPDev Kit/PSPFramework.Utilities/PSP_DebugOpt"\
	-L"F:/SEED TFS/PSPDev Kit/PSPFramework.Maths/PSP_DebugOpt"\
	-L"F:/SEED TFS/PSPDev Kit/PSPFramework/PSP_DebugOpt"\
	-L$(SCE_PSP_HW_ROOT)/lib\
	-Wl,-r -Wl,-dc\
	-T $(LCFILE)\
	-g\

OBJS=\
	"PSP_DebugOpt/main.obj"\
	"PSP_DebugOpt/My_Particle.obj"\

CST_OBJS=\

CST_OUTS=\

CUSTOM: $(CST_OUTS) $(CST_OBJS)

COMPILE: $(OBJS)

"PSP_DebugOpt/main.obj":
	@echo ProDG Compiling "f:/3rd_year/08341/psp/particle/particle/main.cpp"
	$(CXX) $(CXX_FLAGS) "f:/3rd_year/08341/psp/particle/particle/main.cpp" -o $@

"PSP_DebugOpt/My_Particle.obj":
	@echo ProDG Compiling "f:/3rd_year/08341/psp/particle/particle/My_Particle.cpp"
	$(CXX) $(CXX_FLAGS) "f:/3rd_year/08341/psp/particle/particle/My_Particle.cpp" -o $@

LINK: "PSP_DebugOpt/tempprx.obj"

"PSP_DebugOpt/tempprx.obj" : $(CST_OBJS) $(OBJS) $(LCFILE)
	@echo ProDG Linking $@
	$(LD) $(LD_FLAGS) --start-group $(CST_OBJS) $(OBJS) $(LIBS) --end-group -o $@

