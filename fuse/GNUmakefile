# -Wno-return-type -Wno-implicit-int -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast

.PHONY: all clean test
test:
	gcc test.c -o test flist.c fctx.c fdef.c fvcpu.c fbcc.c fbcp.c ffnmap.c -Wno-return-type -Wno-implicit-int -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -O2
	gcc testbc.c -o testbc flist.c fctx.c fdef.c fvcpu.c fbcc.c fbcp.c ffnmap.c -Wno-return-type -Wno-implicit-int -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -O2