{$M $1000,0,0,0}
Program lab1;
Uses Dos, Crt;
Var
   OldHandler: Procedure;
   c, c1: Word;
   control: Word;
   enabled: Boolean;
   sound_enabled: Boolean;
   controls: Byte absolute $40:$17;

{$F+}

Procedure Handler; Interrupt;
Var
   mask: Byte;
Begin
     mask:=2;
     c1:=c;
     c:=Port[$60];
     if c=1 then
        enabled := not enabled;
     if ((c = 6) and (controls and mask=mask)) then
         sound_enabled := not sound_enabled;
     if enabled then
        Begin
             write('; code=', c, ' : ', controls, ';');
             If c = c1 + 128 then
                writeln;
        End;
     if sound_enabled then
        Begin
            sound(1000);
            delay(50);
            nosound;
        End;
     Inline($9C);
     OldHandler;
End;
{$F-}

Begin
     enabled:=false;
     GetIntVec($9, @OldHandler);
     SetIntVec($9, Addr(Handler));
     Keep(0);
End.
End;
