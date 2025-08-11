set pagination off
set logging file .debug_combined/gdb_combined.log
set logging on
record
break main
run < input.txt
echo "\n=== Backtrace complète ===\n"
backtrace full
echo "\n=== Variables locales ===\n"
info locals
echo "\n=== Registres ===\n"
info registers
echo "\n=== Disassembly autour du PC ===\n"
x/20i $pc

echo "\n=== Stepi: progression de 5 instructions ===\n"
set $__steps = 5
while $__steps > 0
  stepi
  info registers
  set $__steps = $__steps - 1
end

echo "\n=== Tentative reverse-step (si supporté) ===\n"
reverse-step
backtrace full

quit
