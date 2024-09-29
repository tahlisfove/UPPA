with TEXT_IO; use TEXT_IO;

procedure giratoire is
   package int_io is new Integer_io(integer);
   use int_io;

   -- nombre de voies dans le giratoire
   NbVoie : Integer := 5;

   -- interface Typevoie
   Subtype Typevoie is Integer range 0..NbVoie-1;

   -- interface voiture
   task type voiture(v:Typevoie) is end voiture;

   -- interface carrefour
   protected type Giratoire is
      -- signal d'entree dans le carrefour
      entry entree(Typevoie);
      -- signal de sortie du carrefour
      procedure sortir;
   private
      CAP_MAX : Integer := 20;
      nbvoiture : Integer := 0;
      VoieCourante : Integer := 0;
      CarrefourVide : Boolean := true;
      i : Integer := 0;
   end Giratoire;

   G : Giratoire;

   -- body Giratoire
   protected body Giratoire is

      -- entrée giratoire 
      entry entree(for voie in Typevoie) when (voie = VoieCourante and nbvoiture < CAP_MAX) is 
      begin
         nbvoiture := nbvoiture + 1;
         VoieCourante := voie;
         CarrefourVide := false;
         put_line(" * Une voiture entre voie" & Integer'Image(voie) & " *");
      end entree;

      -- sortir giratoire
      procedure sortir is
      begin
         nbvoiture := nbvoiture - 1;
         if (nbvoiture = 0) then        
            i := VoieCourante + 1 mod NbVoie;
            VoieCourante := -1;

            -- recherche de la prochaine voie courante
            while entree(i)'Count = 0 loop
               i := i + 1 mod NbVoie;
            end loop;
               VoieCourante := i;
               CarrefourVide := true;
         end if;
      end sortir;

   end Giratoire;

   task body voiture is begin
      put_line("Voiture attente voie" & Integer'Image(v));
      delay 1.0;
      G.entree(v);
      put_line("sortie du giratoire");
      G.sortir;
   end voiture;

   v1: voiture(4);
   v2: voiture(2);
   v3: voiture(3);
   v4: voiture(1);
   v5: voiture(3);
   v6: voiture(0);
   v7: voiture(3);
   v8: voiture(1);

begin
    null;
end giratoire;