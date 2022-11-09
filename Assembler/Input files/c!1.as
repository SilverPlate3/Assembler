 prn -5 
 bne 	W 
 sub 	@r1, @r4 
;; file bs.as
 bne WKSDIMJ123 
 jmp W 
 B2: mov @r3 ,B2 
LOOP: jmp L1 
END: stop 
STR: .string "AbC123!"
T: .data +22 , -32, -1
.extern W
.entry B2 
.entry LOOP 
L1: inc T 

 .extern 	WKSDIMJ123 
