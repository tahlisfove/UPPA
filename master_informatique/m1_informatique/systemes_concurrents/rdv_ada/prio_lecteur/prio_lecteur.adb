with TEXT_IO; use TEXT_IO;

-- un lecteur et un redacteur avec un tampon de taille N
procedure prio_lecteur is
   package int_io is new Integer_io(integer);
   use int_io;

   -- Interface  Magasinier
   task type Magasinier is
      entry debut_lect;
      entry fin_lect;
      entry debut_red;
      entry fin_red;
   end Magasinier;

   M : Magasinier;

   -- Interface lecteur
   task type lecteur is end lecteur;

   -- Interface redacteur
   task type redacteur is end redacteur;

   -- Body Magasinier
   task body Magasinier is

      nblect, nbred, nblectatt : Integer := 0;

   begin
      loop
         select

            -- début lecture
            when (nbred = 0) => accept debut_lect do
               nblect := nblect + 1;
               put_line("debut lect");
            end debut_lect;

         or

            -- début écriture
            when (nblect + nbred + debut_lect'Count = 0) => accept debut_red do
               nbred := nbred + 1;
               put_line("debut red");
            end debut_red;

         or

            -- fin lecture
            accept fin_lect do
               nblect := nblect - 1;
               put_line("fin lect");
            end fin_lect;

         or

            -- fin écriture
            accept fin_red do
               nbred := nbred - 1;
               put_line("fin red");
            end fin_red;

         end select;
      end loop;
   end Magasinier;
   
   -- corps lecteur
   task body lecteur is
      value : Integer := 1;
   begin
      for i in 1..3 loop
         M.debut_lect;
         put_line(" *" & Integer'Image(i) & " *");
         M.fin_lect;
      end loop;
   end lecteur;

   -- corps redacteur
   task body redacteur is
      value : Integer := 0;
   begin
      for i in 1..3 loop
         M.debut_red;
         put_line(" *" & Integer'Image(i) & " *");
         M.fin_red;
      end loop;
   end redacteur;

   l : lecteur;
   r : redacteur;
   
begin
   null;
end prio_lecteur;