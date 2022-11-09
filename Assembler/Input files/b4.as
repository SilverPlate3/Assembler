;################################################################
;# This input file will fail in order to show you error logging #
;################################################################

MAIN: mdov @r3 ,B2 
.entry 3B2 
LOOP jmp L1 
; file bs.as
B2: .data -2,-9,	-15
 prn -5 
 bne W 
 sub @r1
 bne WKSDIMJ123
 .extern 	WKSDIMJ123 
L1: inc T!
.entry LOOP 
 jmp W 
END: stop 
STR: .string "AbC123!
T: .data +22 , -32, 34
.extern W