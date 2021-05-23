cmd_/home/thelshell/linux/tools/labs/skels/./kernel_modules/4-multi-mod/mod2.o := gcc -Wp,-MMD,/home/thelshell/linux/tools/labs/skels/./kernel_modules/4-multi-mod/.mod2.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/8/include -I./arch/x86/include -I./arch/x86/include/generated  -I./include -I./arch/x86/include/uapi -I./arch/x86/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/kconfig.h -include ./include/linux/compiler_types.h -D__KERNEL__ -fmacro-prefix-map=./= -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Wno-format-security -std=gnu89 -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -m32 -msoft-float -mregparm=3 -freg-struct-return -fno-pic -mpreferred-stack-boundary=2 -march=i686 -Wa,-mtune=generic32 -ffreestanding -Wno-sign-compare -fno-asynchronous-unwind-tables -mindirect-branch=thunk-extern -mindirect-branch-register -fno-jump-tables -fno-delete-null-pointer-checks -Wno-frame-address -Wno-format-truncation -Wno-format-overflow -O2 --param=allow-store-data-races=0 -Wframe-larger-than=1024 -fstack-protector-strong -Wno-unused-but-set-variable -Wimplicit-fallthrough -Wno-unused-const-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -gdwarf-4 -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wno-stringop-truncation -Wno-array-bounds -Wno-stringop-overflow -Wno-restrict -Wno-maybe-uninitialized -fno-strict-overflow -fno-stack-check -fconserve-stack -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -fcf-protection=none -Wno-packed-not-aligned -Wno-unused-function -Wno-unused-label -Wno-unused-variable  -DMODULE  -DKBUILD_BASENAME='"mod2"' -DKBUILD_MODNAME='"multi_mod"' -c -o /home/thelshell/linux/tools/labs/skels/./kernel_modules/4-multi-mod/mod2.o /home/thelshell/linux/tools/labs/skels/./kernel_modules/4-multi-mod/mod2.c

source_/home/thelshell/linux/tools/labs/skels/./kernel_modules/4-multi-mod/mod2.o := /home/thelshell/linux/tools/labs/skels/./kernel_modules/4-multi-mod/mod2.c

deps_/home/thelshell/linux/tools/labs/skels/./kernel_modules/4-multi-mod/mod2.o := \
  include/linux/kconfig.h \
    $(wildcard include/config/cc/version/text.h) \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  include/linux/compiler_attributes.h \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arm64.h) \
    $(wildcard include/config/retpoline.h) \
    $(wildcard include/config/arch/use/builtin/bswap.h) \

/home/thelshell/linux/tools/labs/skels/./kernel_modules/4-multi-mod/mod2.o: $(deps_/home/thelshell/linux/tools/labs/skels/./kernel_modules/4-multi-mod/mod2.o)

$(deps_/home/thelshell/linux/tools/labs/skels/./kernel_modules/4-multi-mod/mod2.o):
