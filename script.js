
var xmlhttp = new XMLHttpRequest();
var url = "https://thesimpsonsquoteapi.glitch.me/quotes";

xmlhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
        var myArr = JSON.parse(this.responseText);
        myFunction(myArr);
    }
};
xmlhttp.open("GET", url, true);
xmlhttp.send();

function myFunction(arr) {
    var out = "";
    var i;
    for (i = 0; i < arr.length; i++) {
        out += '<p href="' + arr[i].url + '">' +
            arr[i].quote + '</a><br>';
    }
    document.getElementById("id01").innerHTML =  out;
}




var data = null;

var xhr = new XMLHttpRequest();
xhr.withCredentials = true;

xhr.addEventListener("readystatechange", function () {
    if (this.readyState === this.DONE) {
        console.log(this.responseText);

        var printResult = JSON.parse(this.responseText);
        console.log(printResult.value);
        document.getElementById("id02").innerHTML = "<b>Chuck Quote: </b>" + "<br><br>" + printResult.value;
    }
});

xhr.open("GET", "https://matchilling-chuck-norris-jokes-v1.p.rapidapi.com/jokes/random");
xhr.setRequestHeader("x-rapidapi-host", "matchilling-chuck-norris-jokes-v1.p.rapidapi.com");
xhr.setRequestHeader("x-rapidapi-key", "159ea36812mshd7896f392a83ae5p169a08jsn24aba9ca64a2");
xhr.setRequestHeader("accept", "application/json");

xhr.send();


var data = null;

var xhr = new XMLHttpRequest();
xhr.withCredentials = true;

xhr.addEventListener("readystatechange", function () {
    if (this.readyState === this.DONE) {
        console.log(this.responseText);

        var printResult2 = JSON.parse(this.responseText);
       // console.log(printResult2.definition);
        document.getElementById("id03").innerHTML = "<b>Word of the day" + " = " +  printResult2.list[1].word + "</b><br><br>"  + printResult2.list[6].example;

    }
});

xhr.open("GET", "https://mashape-community-urban-dictionary.p.rapidapi.com/define?term=random");
xhr.setRequestHeader("x-rapidapi-host", "mashape-community-urban-dictionary.p.rapidapi.com");
xhr.setRequestHeader("x-rapidapi-key", "159ea36812mshd7896f392a83ae5p169a08jsn24aba9ca64a2");

xhr.send(data);

