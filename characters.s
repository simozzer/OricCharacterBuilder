#DEFINE CHARSET_BASE_ADDR $B400

#DEFINE ASCII_SPACE 32
#DEFINE ASCII_EXCLAMATION_ADDR CHARSET_BASE_ADDR + (33 *8)
#DEFINE ASCII_DOUBLE_QUOTE 34



CharData 
  .byt 63,33,33,33,33,33,33,63 ; emptty square (33)
  .byt 63,33,45,45,45,45,33,63 ; filled square (34)

_InitializeCharacters
.(
  ldy #0
  loop
  lda CharData,Y
  sta ASCII_EXCLAMATION_ADDR,Y
  iny 
  cpy #16
  bne loop
  rts
.)
