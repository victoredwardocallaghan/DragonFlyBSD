# $FreeBSD$


.if !make(install)
.if !defined(NO_CLANG_FULL)
_libclangstaticanalyzer= \
	libclangstaticanalyzercheckers \
	libclangstaticanalyzercore \
	libclangstaticanalyzerfrontend
_libclangarcmigrate= \
	libclangarcmigrate
.endif # NO_CLANG_FULL
.if !defined(NO_CLANG_FULL) || !defined(NO_LLDB)
_libclangrewriter= \
	libclangrewritecore \
	libclangrewritefrontend
.endif # (NO_CLANG_FULL || NO_LLDB)

SUBDIR=	libclanganalysis \
	${_libclangarcmigrate} \
	libclangast \
	libclangbasic \
	libclangcodegen \
	libclangdriver \
	libclangedit \
	libclangfrontend \
	libclangfrontendtool \
	libclanglex \
	libclangparse \
	${_libclangrewriter} \
	libclangsema \
	libclangserialization \
	${_libclangstaticanalyzer} \
	\
	libllvmanalysis \
	libllvmasmparser \
	libllvmasmprinter \
	libllvmbitreader \
	libllvmbitwriter \
	libllvmcodegen \
	libllvmcore \
	libllvminstcombine \
	libllvminstrumentation \
	libllvmipa \
	libllvmipo \
	libllvmirreader \
	libllvmlinker \
	libllvmmc \
	libllvmmcparser \
	libllvmobjcarcopts \
	libllvmobject \
	libllvmoption \
	libllvmscalaropts \
	libllvmselectiondag \
	libllvmsupport \
	libllvmtablegen \
	libllvmtarget \
	libllvmtransformutils \
	libllvmvectorize \
	\
	libllvmarmasmparser \
	libllvmarmcodegen \
	libllvmarmdesc \
	libllvmarmdisassembler \
	libllvmarminfo \
	libllvmarminstprinter \
	libllvmmipsasmparser \
	libllvmmipscodegen \
	libllvmmipsdesc \
	libllvmmipsdisassembler \
	libllvmmipsinfo \
	libllvmmipsinstprinter \
	libllvmpowerpcasmparser \
	libllvmpowerpccodegen \
	libllvmpowerpcdesc \
	libllvmpowerpcinfo \
	libllvmpowerpcinstprinter \
	libllvmsparcasmparser \
	libllvmsparccodegen \
	libllvmsparcdesc \
	libllvmsparcdisassembler \
	libllvmsparcinfo \
	libllvmsparcinstprinter \
	libllvmx86asmparser \
	libllvmx86codegen \
	libllvmx86desc \
	libllvmx86disassembler \
	libllvmx86info \
	libllvmx86instprinter \
	libllvmx86utils

.if !defined(NO_CLANG_EXTRAS)
SUBDIR+=libllvmdebuginfo
.endif # NO_CLANG_EXTRAS
.if !defined(NO_CLANG_EXTRAS) || !defined(NO_LLDB)
SUBDIR+=libllvmexecutionengine \
	libllvminterpreter \
	libllvmjit \
	libllvmmcdisassembler \
	libllvmmcjit \
	libllvmruntimedyld
.endif # NO_CLANG_EXTRAS | NO_LLDB

.if !defined(NO_LLDB)
SUBDIR+=liblldb \
	\
	liblldbAPI \
	liblldbBreakpoint \
	liblldbCommands \
	liblldbCore \
	liblldbDataFormatters \
	liblldbExpression \
	liblldbHostCommon \
	liblldbHostFreeBSD \
	liblldbInterpreter \
	liblldbSymbol \
	liblldbTarget \
	liblldbUtility \
	\
	liblldbPluginABISysV_x86_64 \
	liblldbPluginCXXItaniumABI \
	liblldbPluginDisassemblerLLVM \
	liblldbPluginDynamicLoaderStatic \
	liblldbPluginDynamicLoaderPosixDYLD \
	liblldbPluginInstructionARM \
	liblldbPluginObjectContainerBSDArchive \
	liblldbPluginObjectFileELF \
	liblldbPluginPlatformFreeBSD \
	liblldbPluginPlatformGDB \
	liblldbPluginProcessElfCore \
	liblldbPluginProcessFreeBSD \
	liblldbPluginProcessGDBRemote \
	liblldbPluginProcessPOSIX \
	liblldbPluginProcessUtility \
	liblldbPluginSymbolFileDWARF \
	liblldbPluginSymbolFileSymtab \
	liblldbPluginSymbolVendorELF \
	liblldbPluginUnwindAssemblyInstEmulation \
	liblldbPluginUnwindAssemblyX86
.endif # NO_LLDB

.endif # !make(install)

SUBDIR+= include

SUBDIR_PARALLEL=

.include <bsd.subdir.mk>
