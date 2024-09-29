with TEXT_IO; use TEXT_IO;

-- un lecteur et un redacteur avec un tampon de taille N
procedure prio_redacteur_protege is
   package int_io is new Integer_io(integer);
   use int_io;

   -- interface  Magasinier
   protected type Magasinier is
        entry debut_lect;
        procedure fin_lect;
        entry debut_red;
        procedure fin_red;
   private
        nblect, nbred, nblectatt, nbredatt : Integer := 0;
   end Magasinier;

   M : Magasinier;

   -- interface lecteur
   task type lecteur is end lecteur;

   -- interface redacteur
   task type redacteur is end redacteur;

   -- body Magasinier
   protected body Magasinier is
   
      -- début lecture
      entry debut_lect when (nbred + debut_red'Count = 0) is
      begin
         nblect:=nblect +1;
         put_line ("debut lect");
      end debut_lect;

      -- début écriture
      entry debut_red when (nbred + nblect = 0) is
      begin
         nbred:=nbred+1;
         put_line ("debut red");
      end debut_red;

      -- fin lecture
      procedure fin_lect is
      begin
         nblect:=nblect -1;
         put_line ("fin lect");
      end fin_lect;

      -- fin écriture
      procedure fin_red is
      begin
         nbred:=nbred -1;
         put_line ("fin red");
      end fin_red;

   end Magasinier;

   -- corps lecteur
   task body lecteur is
   begin
      for i in 1..3 loop
         M.debut_lect;
         put_line(" *" & Integer'Image(i) & " *");
         M.fin_lect;
      end loop;
   end lecteur;

   -- corps redacteur
   task body redacteur is
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
end prio_redacteur_protege;