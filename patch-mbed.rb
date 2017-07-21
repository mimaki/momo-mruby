#! /usr/bin/env ruby
require 'fileutils'

STACKSIZE = 0x00008000
HEAPSIZE  = 0x00400000

PATCHNAME = 'mbed.patch'

# File name of bootstrap
startup = File.join('mbed-os', 'targets', 'TARGET_RENESAS', 'TARGET_RZ_A1H', 'device', 'TOOLCHAIN_GCC_ARM', 'startup_RZ1AH.S')
# p startup

stack = File.readlines(startup).grep /\.EQU.*USR_Stack_Size.*,.*0x[0-9A-Fa-f]*/
heap  = File.readlines(startup).grep /\.EQU.*Heap_Size.*,.*0x[0-9A-Fa-f]*/
# p stack, heap

# Get current stack/heap size
cur_stack = stack[0].match(/0x[0-9A-Fa-f]*/)[0].to_i(16)
cur_heap  = heap[0].match(/0x[0-9A-Fa-f]*/)[0].to_i(16)
# p cur_stack, cur_heap

if cur_stack != STACKSIZE || cur_heap != HEAPSIZE
  puts <<EOS
Change mbed-os memory configurations
  User stack size  : #{cur_stack/1024}KB -> #{STACKSIZE/1024}KB
  Heap memory size : #{cur_heap/1024}KB -> #{HEAPSIZE/1024}KB
EOS

  patch = <<EOS
--- mbed-os/targets/TARGET_RENESAS/TARGET_RZ_A1H/device/TOOLCHAIN_GCC_ARM/startup_RZ1AH.S	2017-07-21 10:28:33.000000000 +0900
+++ mbed-os/targets/TARGET_RENESAS/TARGET_RZ_A1H/device/TOOLCHAIN_GCC_ARM/startup_RZ1AH.S.new	2017-07-21 10:30:30.000000000 +0900
@@ -77,7 +77,7 @@
     .EQU    ABT_Stack_Size  , 0x00000100
     .EQU    FIQ_Stack_Size  , 0x00000100
     .EQU    IRQ_Stack_Size  , 0x00008000
-    .EQU    USR_Stack_Size  , 0x#{sprintf("%08x", cur_stack)}
+    .EQU    USR_Stack_Size  , 0x#{sprintf("%08x", STACKSIZE)}
 
     .EQU    ISR_Stack_Size, (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + FIQ_Stack_Size + IRQ_Stack_Size)
 
@@ -96,7 +96,7 @@
 
 @ Heap Configuration
 
-    .EQU    Heap_Size       , 0x#{sprintf("%08x", cur_heap)}
+    .EQU    Heap_Size       , 0x#{sprintf("%08x", HEAPSIZE)}
 
     .section .heap
     .align 3
EOS
  # Create patch file
  File.open(PATCHNAME, 'w') {|f| f.write patch}
  # Apply patch to bootstrap
  `patch -u #{startup} < #{PATCHNAME}`
  # cleanup
  FileUtils.rm_f PATCHNAME
end
