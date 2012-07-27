# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := libsrtp
DEFS_Debug := '-DHAVE_STDLIB_H' \
	'-DHAVE_STRING_H' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DCPU_CISC' \
	'-DSIZEOF_UNSIGNED_LONG=8' \
	'-DSIZEOF_UNSIGNED_LONG_LONG=8' \
	'-DHAVE_STDINT_H' \
	'-DHAVE_INTTYPES_H' \
	'-DCHROMIUM_BUILD' \
	'-DUSE_NSS=1' \
	'-DTOOLKIT_USES_GTK=1' \
	'-DGTK_DISABLE_SINGLE_INCLUDES=1' \
	'-DENABLE_REMOTING=1' \
	'-DENABLE_P2P_APIS=1' \
	'-DENABLE_CONFIGURATION_POLICY' \
	'-DENABLE_INPUT_SPEECH' \
	'-DENABLE_NOTIFICATIONS' \
	'-DENABLE_GPU=1' \
	'-DENABLE_EGLIMAGE=1' \
	'-DUSE_SKIA=1' \
	'-DENABLE_REGISTER_PROTOCOL_HANDLER=1' \
	'-DENABLE_WEB_INTENTS=1' \
	'-DENABLE_PLUGIN_INSTALLATION=1' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=1' \
	'-DWTF_USE_DYNAMIC_ANNOTATIONS=1' \
	'-D_DEBUG'

# Flags passed to all source files.
CFLAGS_Debug := -pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Wno-format \
	-Wno-unused-result \
	-O0 \
	-g

# Flags passed to only C files.
CFLAGS_C_Debug := 

# Flags passed to only C++ files.
CFLAGS_CC_Debug := -fno-rtti \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden \
	-Wno-deprecated

INCS_Debug := -Ithird_party/libsrtp/config \
	-Ithird_party/libsrtp/srtp/include \
	-Ithird_party/libsrtp/srtp/crypto/include

DEFS_Release := '-DHAVE_STDLIB_H' \
	'-DHAVE_STRING_H' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DCPU_CISC' \
	'-DSIZEOF_UNSIGNED_LONG=8' \
	'-DSIZEOF_UNSIGNED_LONG_LONG=8' \
	'-DHAVE_STDINT_H' \
	'-DHAVE_INTTYPES_H' \
	'-DCHROMIUM_BUILD' \
	'-DUSE_NSS=1' \
	'-DTOOLKIT_USES_GTK=1' \
	'-DGTK_DISABLE_SINGLE_INCLUDES=1' \
	'-DENABLE_REMOTING=1' \
	'-DENABLE_P2P_APIS=1' \
	'-DENABLE_CONFIGURATION_POLICY' \
	'-DENABLE_INPUT_SPEECH' \
	'-DENABLE_NOTIFICATIONS' \
	'-DENABLE_GPU=1' \
	'-DENABLE_EGLIMAGE=1' \
	'-DUSE_SKIA=1' \
	'-DENABLE_REGISTER_PROTOCOL_HANDLER=1' \
	'-DENABLE_WEB_INTENTS=1' \
	'-DENABLE_PLUGIN_INSTALLATION=1' \
	'-DNDEBUG' \
	'-DNVALGRIND' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=0'

# Flags passed to all source files.
CFLAGS_Release := -pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Wno-format \
	-Wno-unused-result \
	-O2 \
	-fno-ident \
	-fdata-sections \
	-ffunction-sections

# Flags passed to only C files.
CFLAGS_C_Release := 

# Flags passed to only C++ files.
CFLAGS_CC_Release := -fno-rtti \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden \
	-Wno-deprecated

INCS_Release := -Ithird_party/libsrtp/config \
	-Ithird_party/libsrtp/srtp/include \
	-Ithird_party/libsrtp/srtp/crypto/include

OBJS := $(obj).target/$(TARGET)/third_party/libsrtp/srtp/srtp/ekt.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/srtp/srtp.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/cipher/aes.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/cipher/aes_cbc.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/cipher/aes_icm.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/cipher/cipher.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/cipher/null_cipher.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/hash/auth.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/hash/hmac.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/hash/null_auth.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/hash/sha1.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/kernel/alloc.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/kernel/crypto_kernel.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/kernel/err.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/kernel/key.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/math/datatypes.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/math/gf2_8.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/math/stat.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/replay/rdb.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/replay/rdbx.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/replay/ut_sim.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/rng/ctr_prng.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/rng/prng.o \
	$(obj).target/$(TARGET)/third_party/libsrtp/srtp/crypto/rng/rand_source.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := -pthread \
	-Wl,-z,noexecstack \
	-fPIC \
	-B$(builddir)/../../third_party/gold

LDFLAGS_Release := -pthread \
	-Wl,-z,noexecstack \
	-fPIC \
	-B$(builddir)/../../third_party/gold \
	-Wl,-O1 \
	-Wl,--as-needed \
	-Wl,--gc-sections

LIBS := 

$(obj).target/third_party/libsrtp/libsrtp.a: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/third_party/libsrtp/libsrtp.a: LIBS := $(LIBS)
$(obj).target/third_party/libsrtp/libsrtp.a: TOOLSET := $(TOOLSET)
$(obj).target/third_party/libsrtp/libsrtp.a: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,alink)

all_deps += $(obj).target/third_party/libsrtp/libsrtp.a
# Add target alias
.PHONY: libsrtp
libsrtp: $(obj).target/third_party/libsrtp/libsrtp.a

# Add target alias to "all" target.
.PHONY: all
all: libsrtp

