; Assembly code for SimpleLang

.data
a = 0
b = 1
c = 2


.text
ldi A 10
mov M A %a

ldi A 20
mov M A %b

mov A M %a
mov B M %b
add
mov M A %c

mov A M %c
ldi B 30
cmp
jne %skip
mov A M %b
ldi B 10
sub
mov M A %c

skip:
hlt
