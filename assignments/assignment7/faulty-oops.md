## Oops message
'''
# echo “hello_world” > /dev/faulty
Unable to handle kernel NULL pointer dereference at virtual address 0000000000000000
Mem abort info:
  ESR = 0x0000000096000044
  EC = 0x25: DABT (current EL), IL = 32 bits
  SET = 0, FnV = 0
  EA = 0, S1PTW = 0
  FSC = 0x04: level 0 translation fault
Data abort info:
  ISV = 0, ISS = 0x00000044, ISS2 = 0x00000000
  CM = 0, WnR = 1, TnD = 0, TagAccess = 0
  GCS = 0, Overlay = 0, DirtyBit = 0, Xs = 0
user pgtable: 4k pages, 48-bit VAs, pgdp=0000000041b5d000
[0000000000000000] pgd=0000000000000000, p4d=0000000000000000
Internal error: Oops: 0000000096000044 [#1] SMP
Modules linked in: hello(O) scull(O) faulty(O)
CPU: 0 UID: 0 PID: 152 Comm: sh Tainted: G           O       6.12.47 #1
Tainted: [O]=OOT_MODULE
Hardware name: linux,dummy-virt (DT)
pstate: 80000005 (Nzcv daif -PAN -UAO -TCO -DIT -SSBS BTYPE=--)
pc : faulty_write+0x8/0x10 [faulty]
lr : vfs_write+0xb4/0x380
sp : ffff800080e83d30
x29: ffff800080e83da0 x28: ffff000001b51f00 x27: 0000000000000000
x26: 0000000000000000 x25: 0000000000000000 x24: 0000000000000000
x23: 0000000040000000 x22: 0000000000000012 x21: 0000aaaad68f44c0
x20: 0000aaaad68f44c0 x19: ffff000001c3a000 x18: 0000000000000000
x17: 0000000000000000 x16: 0000000000000000 x15: 0000000000000000
x14: 0000000000000000 x13: 0000000000000000 x12: 0000000000000000
x11: 0000000000000000 x10: 0000000000000000 x9 : 0000000000000000
x8 : 0000000000000000 x7 : 0000000000000000 x6 : 0000000000000000
x5 : 0000000000000000 x4 : ffff800078cb0000 x3 : ffff800080e83dc0
x2 : 0000000000000012 x1 : 0000000000000000 x0 : 0000000000000000
Call trace:
 faulty_write+0x8/0x10 [faulty]
 ksys_write+0x74/0x110
 __arm64_sys_write+0x1c/0x30
 invoke_syscall+0x54/0x120
 el0_svc_common.constprop.0+0x40/0xe0
 do_el0_svc+0x1c/0x30
 el0_svc+0x30/0x100
 el0t_64_sync_handler+0x120/0x130
 el0t_64_sync+0x190/0x194
Code: ???????? ???????? d2800001 d2800000 (b900003f) 
---[ end trace 0000000000000000 ]---
'''

## Analysis
First row *"Unable to handle kernel NULL pointer dereference at virtual address 0000000000000000"* shows actual problem happend. Call trace points to the function __faulty_write__ in the module __faulty__. In source code of that function we can actualy see the mentioned null pointer dereferencing.
