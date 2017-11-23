{$M $1000,0,0,0}
Program lab1;
Uses Dos, Crt;
Var
   OldTimerHandler: Procedure;
   enabled: Boolean;
   alarm_enabled: Boolean;
   alarm_ticks: Word;
   counter: Word;
   sys_counter: Word absolute $0040:$006C;
   period_ticks: Integer;
   period_alarm: Integer;
{$F+}

Procedure TimerHandler; Interrupt;
Begin
    Inc(counter);
    Inc(alarm_ticks);
    {write('counter=', counter, '; ');}
    if (counter mod 3  = 0) then nosound;

    if (counter mod period_ticks = 0) and (not alarm_enabled) then
       begin
            enabled := not enabled;
            sound(counter);

       end;
    if (counter mod period_alarm = 0) then
       begin
            alarm_enabled:=true;
            alarm_ticks:=0;
            nosound;
       end;

    if (alarm_enabled) then
    begin
       if (alarm_ticks < 15) then
          begin
               nosound;
               sound(440 + (alarm_ticks * 100));
          end
       else
       if (alarm_ticks < 30) then
          begin
               nosound;
               sound(440 + 1500 - ((alarm_ticks - 15) * 100));
          end;

       if (alarm_ticks >= 30) then alarm_enabled:=false;
    end;
{    if (enabled and counter mod 18 == 0) then
       begin
            sound(counter);
       end;



       }
    Inline($9C);
    OldTimerHandler;
    {if (counter % 2 == 0) then
        begin

        end;}
End;
{$F-}
Var
   code_ticks: Integer;
   code_alarm: Integer;
   readed_ticks: Real;
   readed_alarm: Real;
Begin
     enabled:=false;
     alarm_enabled:=false;
     counter:=0;
     period_ticks := 18;
     period_ala      rm := 364;
     if ParamCount <> 2 then
        begin
             writeln('Wrong parameters count.');
             halt;
        end;
     Val(ParamStr(1), readed_ticks, code_ticks);
     Val(ParamStr(2), readed_alarm, code_alarm);
     if (code_ticks <> 0) or (code_alarm <> 0) then
     begin
          writeln('Wrong arguments value');
          halt;
     end;
     readed_ticks := readed_ticks * 18;
     readed_alarm := readed_alarm * 60 * 18;
     period_ticks := round(readed_ticks);
     period_alarm := round(readed_alarm);
{     GetIntVec($9, @OldHandler);
     SetIntVec($9, Addr(Handler)); }
     GetIntVec($8, @OldTimerHandler);
     SetIntVec($8, Addr(TimerHandler));
     Keep(0);
End.
End;
