
SECTIONS
{
	. = 0x400000;
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
ENTRY(init_start)
