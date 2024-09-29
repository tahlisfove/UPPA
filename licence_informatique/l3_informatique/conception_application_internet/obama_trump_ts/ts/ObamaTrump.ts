window.addEventListener('DOMContentLoaded', (event: Event) => {
    Game.Run();
});

class Game {
    static Data = new Array(
        {
            Answer: /O[b]+a[m]+a/i, // ObbamMa
            URLs: [
                "./img/Obama-1.jpg",
                "./img/Obama-2.jpg"],
            Time: 10000
        },
        {
            Answer: /Tr[ou]+mpe?/i, // 'Trompe' OK!
            URLs: [
                "./img/Trump-1.jpg",
                "./img/Trump-2.jpg"],
            Time: 10000
        }
        // Etc.
    );

    static Run() {
        /* On récupère ici les élements du DOM, attention ce dernier doit être chargé... */
        const photography: HTMLCanvasElement = window.document.getElementById("photography") as HTMLCanvasElement;
        photography.width = 600;
        photography.height = 400;

        const character = window.Math.floor(window.Math.random() * Game.Data.length);

        const image = new Image();
        image.onload = () => {
            photography.getContext('2d')!.drawImage(image, 0, 0, photography.width, photography.height);
        };
        image.src = Game.Data[character].URLs[window.Math.floor(window.Math.random() * Game.Data[character].URLs.length)]; // Loading image from here…

        const complete_response = new Promise(result => {
            const response = window.document.getElementById("response") as HTMLInputElement;
            response.addEventListener('change', (event: Event) => {
                // L'événement 'change' est produit par JavaScript lorsque l'utilisateur a tapé "Return"...
                if (Game.Data[character].Answer.test((event.target as HTMLInputElement).value)) // RegExp
                    result("gained");
                else
                    result("lost");
            });
        });

        const incomplete_response = new Promise(result => {
            const response = window.document.getElementById("response") as HTMLInputElement;
            response.addEventListener('input', (event: Event) => {
                // L'événement 'input' est produit par JavaScript lorsque l'utilisateur a tapé un seul caractère...
                if (Game.Data[character].Answer.test((event.target as HTMLInputElement).value)) // RegExp
                    result("gained");
            });
        });

        let start = 0;
        let timer: number;
        const time_out = new Promise(result => {
            timer = window.setInterval(() => {
                start += 100; // 100ms
                if (start >= Game.Data[character].Time) {
                    window.clearInterval(timer);
                    result("lost");
                }
                window.document.getElementById("timer")!.innerHTML = (Game.Data[character].Time - start).toString();
            }, Game.Data[character].Time / 100); // 100ms
        });

        Promise.race([complete_response, incomplete_response, time_out]).then(result => {
            const context: CanvasRenderingContext2D = photography.getContext('2d') as CanvasRenderingContext2D;
            context.font = "30px Comic Sans MS";
            context.fillStyle = "red";
            context.textAlign = "center";
            const response = window.document.getElementById("response") as HTMLInputElement;
            context.fillText(result + " : " + response.value, photography.width / 2, photography.height / 2);
            response.value = "";
        });
    }
}
