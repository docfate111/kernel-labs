cmd_/home/thelshell/linux/tools/labs/skels/./kernel_modules/1-2-test-mod/modules.order := {   echo /home/thelshell/linux/tools/labs/skels/./kernel_modules/1-2-test-mod/hello_mod.ko; :; } | awk '!x[$$0]++' - > /home/thelshell/linux/tools/labs/skels/./kernel_modules/1-2-test-mod/modules.order
