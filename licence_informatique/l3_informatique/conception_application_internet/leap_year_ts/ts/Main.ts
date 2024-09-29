// import Leap_year from "./Leap_year"; // Compilation time...
import Leap_year from "./Leap_year.js"; // Run time...

// webpack and webpack-cli are loaded as dev. dep. to solve the problem (https://webpack.js.org/guides/getting-started/)!

window.onload = function () {
    try {
        window.confirm("2020-05-04: " + Leap_year("2020-05-04"));
        window.confirm("2020202020-05-04: " + Leap_year("2020202020-05-04"));
    } catch (e) {
        window.confirm(e.name + ": " + e.message);
    }
}
