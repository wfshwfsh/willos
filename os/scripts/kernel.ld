ENTRY(start)
SECTIONS
{
	. = 0x100000;
	
	.text :
	{
		*(.text)
		. = ALIGN(4096);
	}

	.data :
	{
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
	}
	
	.bss : 
	{
		*(.bss)
		. = ALIGN(4096);
	}
	
	/DISCARD/ :
	{
		*(.eh_frame .note.GNU-stack)
	}
}
