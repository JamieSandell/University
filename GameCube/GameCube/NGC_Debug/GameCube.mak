####################################################
# NGC Makefile generated for GNU Make by ProDG VSI #
####################################################

.SILENT:
.SUFFIXES:
.SUFFIXES: .c .cpp .cxx .cc .s .asm

unexport MAKEFLAGS
unexport MFLAGS

OUTDIR = NGC_Debug
INTDIR = NGC_Debug

LCFILE = "e:/3rd_year/08356/Purdy/ACW/GameCube/GameCube/ngc.ld"
LIBS=\
	 "base.a"\
	 "os.a"\
	 "exi.a"\
	 "si.a"\
	 "db.a"\
	 "mtx.a"\
	 "dvd.a"\
	 "vi.a"\
	 "demo.a"\
	 "pad.a"\
	 "ai.a"\
	 "ar.a"\
	 "ax.a"\
	 "axfx.a"\
	 "mix.a"\
	 "sp.a"\
	 "am.a"\
	 "axart.a"\
	 "syn.a"\
	 "seq.a"\
	 "dsp.a"\
	 "dtk.a"\
	 "card.a"\
	 "hio.a"\
	 "mcc.a"\
	 "gx.a"\
	 "G2D.a"\
	 "texPalette.a"\
	 "fileCache.a"\
	 "support.a"\
	 "perf.a"\
	 "amcstubs.a"\
	 "odemustubs.a"\

AS=ngccc
AS_FLAGS=\
	-DSN_TARGET_NGC\
	-DHW2\
	-D__SN__\
	-DSNSYS\
	-D__HWSIM=0\
	-DEPPC\
	-DMARLIN=DI\
	-DORCA\
	-DGEKKO\
	-DGX_REV=2\
	-DBUG_CLR_LOAD_DLY\
	-DBUG_XF_STALL\
	-I"C:/Program Files/DolphinSDK1.0/include"\
	-I"C:/Program Files/SN Systems/ngc/include"\
	-I.\
	-c\
	-fdevstudio\
	-g\

CC=ngccc
CC_FLAGS=\
	-DSN_TARGET_NGC\
	-DHW2\
	-D__SN__\
	-DSNSYS\
	-D__HWSIM=0\
	-DEPPC\
	-DMARLIN=DI\
	-DORCA\
	-DGEKKO\
	-DGX_REV=2\
	-DBUG_CLR_LOAD_DLY\
	-DBUG_XF_STALL\
	-I"C:/Program Files/DolphinSDK1.0/include"\
	-I"C:/Program Files/SN Systems/ngc/include"\
	-I.\
	-c\
	-fdevstudio\
	-MMD\
	-g\
	-O0\
	-Wall\
	-fno-exceptions\

CXX=ngccc
CXX_FLAGS=\
	-DSN_TARGET_NGC\
	-DHW2\
	-D__SN__\
	-DSNSYS\
	-D__HWSIM=0\
	-DEPPC\
	-DMARLIN=DI\
	-DORCA\
	-DGEKKO\
	-DGX_REV=2\
	-DBUG_CLR_LOAD_DLY\
	-DBUG_XF_STALL\
	-I"C:/Program Files/DolphinSDK1.0/include"\
	-I"C:/Program Files/SN Systems/ngc/include"\
	-I.\
	-c\
	-fdevstudio\
	-MMD\
	-g\
	-O0\
	-Wall\
	-fno-exceptions\

LD=ngccc
LD_FLAGS=\
	-L"C:/Program Files/DolphinSDK1.0/HW2/lib"\
	-fdevstudio -nostartfiles -T $(LCFILE)\

OBJS=\
	"NGC_Debug/frb-bound-box.obj"\

CST_OBJS=\

CST_OUTS=\

CUSTOM: $(CST_OUTS) $(CST_OBJS)

COMPILE: $(OBJS)

"NGC_Debug/frb-bound-box.obj":
	@echo ProDG Compiling "e:/3rd_year/08356/Purdy/ACW/GameCube/GameCube/frb-bound-box.c"
	$(CC) $(CC_FLAGS) "e:/3rd_year/08356/Purdy/ACW/GameCube/GameCube/frb-bound-box.c" -o $@

LINK: "NGC_Debug/GameCube.elf"

"NGC_Debug/GameCube.elf" : $(CST_OBJS) $(OBJS) $(LCFILE)
	@echo ProDG Linking $@
	$(LD) $(LD_FLAGS) --start-group -lsn -lm -lc -lgcc $(CST_OBJS) $(OBJS) $(LIBS) --end-group -o $@

