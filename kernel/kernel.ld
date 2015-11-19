
SECTIONS
{
	. = 0x200000;
	.text . :{
		*(.text)
	}
	.rodata . : {
		*(.rodata)
	}
	.data . : {
		*(.data)
	}
	.bss . : {
		*(.bss)
	}
}
ENTRY(kernel_bootasm)
