# -Wno-return-type -Wno-implicit-int -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast

.PHONY: all clean test
test:
	gcc test.c -o test fou.c flist.c fctx.c fdef.c fvcpu.c fbcc.c fbcp.c ffnmap.c -Wno-int-conversion -Wno-return-type -Wno-implicit-int -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -O2 -g
	gcc testbc.c -o testbc fou.c flist.c fctx.c fdef.c fvcpu.c fbcc.c fbcp.c ffnmap.c -Wno-int-conversion -Wno-return-type -Wno-implicit-int -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -O2 -g
	gcc fuse.c -o runfuse fou.c flist.c fctx.c fdef.c fvcpu.c fbcc.c fbcp.c ffnmap.c -Wno-int-conversion -Wno-return-type -Wno-implicit-int -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -O2 -g