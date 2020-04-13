# Test file for "Lab4"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0x00, 0x04, 0x00, 0x02 => PORTB: 0, 0, 0, 1; state: Lock, Unlock1, Unlock1, Unlock2"
set state = Lock
setPINA 0x00
continue 5
expectPORTB 0
expect state Lock
setPINA 0x04
continue 5
expectPORTB 0
expect state Unlock1
setPINA 0x00
continue 5
expectPORTB 0
expect state Unlock1
setPINA 0x02
continue 5
expectPORTB 1
expect state Unlock2
checkResult

test "PINA: 0x00, 0x06, 0x00, 0x02 => PORTB: 0, 0, 0, 0; state: Lock, Lock, Lock, Lock"
set state = Lock
setPINA 0x00
continue 5
expectPORTB 0
expect state Lock
setPINA 0x06
continue 5
expectPORTB 0
expect state Lock
setPINA 0x00
continue 5
expectPORTB 0
expect state Lock
setPINA 0x02
continue 5
expectPORTB 0
expect state Lock
checkResult

test "PINA: 0x00, 0x04, 0x06, 0x02 => PORTB: 0, 0, 0, 0; state: Lock, Unlock1, Lock, Lock"
set state = Lock
setPINA 0x00
continue 5
expectPORTB 0
expect state Lock
setPINA 0x04
continue 5
expectPORTB 0
expect state Unlock1
setPINA 0x06
continue 5
expectPORTB 0
expect state Lock
setPINA 0x02
continue 5
expectPORTB 0
expect state Lock
checkResult

test "PINA: 0x00, 0x80 => PORTB: 1, 0; state: Unlock2, Lock"
set state = Unlock2
setPINA 0x00
continue 5
expectPORTB 1
expect state Unlock2
setPINA 0x80
continue 5
expectPORTB 0
expect state Lock
checkResult

test "PINA: 0x00, 0x07 => PORTB: 1, 1; state: Unlock2, Unlock2"
set state = Unlock2
setPINA 0x00
continue 5
expectPORTB 1
expect state Unlock2
setPINA 0x07
continue 5
expectPORTB 1
expect state Unlock2
checkResult

# Add tests below

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
