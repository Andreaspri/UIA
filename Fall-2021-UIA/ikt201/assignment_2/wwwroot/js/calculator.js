
function zero(){
    if (document.getElementById("display").innerHTML != "0")
    {
        document.getElementById("display").innerHTML += "0"
    }
}

function one(){
    if (document.getElementById("display").innerHTML == "0")
    {
        document.getElementById("display").innerHTML = "1"
    }
    else {
        document.getElementById("display").innerHTML += "1"
    }
}

function two(){
    if (document.getElementById("display").innerHTML == "0")
    {
        document.getElementById("display").innerHTML = "2"
    }
    else {
        document.getElementById("display").innerHTML += "2"
    }
}

function three(){
    if (document.getElementById("display").innerHTML == "0")
    {
        document.getElementById("display").innerHTML = "3"
    }
    else {
        document.getElementById("display").innerHTML += "3"
    }
}

function four(){
    if (document.getElementById("display").innerHTML == "0")
    {
        document.getElementById("display").innerHTML = "4"
    }
    else {
        document.getElementById("display").innerHTML += "4"
    }
}

function five(){
    if (document.getElementById("display").innerHTML == "0")
    {
        document.getElementById("display").innerHTML = "5"
    }
    else {
        document.getElementById("display").innerHTML += "5"
    }
}

function six(){
    if (document.getElementById("display").innerHTML == "0")
    {
        document.getElementById("display").innerHTML = "6"
    }
    else {
        document.getElementById("display").innerHTML += "6"
    }
}

function seven(){
    if (document.getElementById("display").innerHTML == "0")
    {
        document.getElementById("display").innerHTML = "7"
    }
    else {
        document.getElementById("display").innerHTML += "7"
    }
}

function eight(){
    if (document.getElementById("display").innerHTML == "0")
    {
        document.getElementById("display").innerHTML = "8"
    }
    else {
        document.getElementById("display").innerHTML += "8"
    }
}

function nine(){
    if (document.getElementById("display").innerHTML == "0")
    {
        document.getElementById("display").innerHTML = "9"
    }
    else {
        document.getElementById("display").innerHTML += "9"
    }
}

function plus(){
    let display = document.getElementById("display").innerHTML
    let last = display.charAt(display.length-1)
    if (last == "-" || last == "/" || last == "*"){
        document.getElementById("display").innerHTML = display.substring(0,display.length-1) + "+"

    }
    else if (last == "+") {
        //pass
    }
    else {
        document.getElementById("display").innerHTML += "+"
    }
}

function minus(){
    let display = document.getElementById("display").innerHTML
    let last = display.charAt(display.length-1)
    if (last == "+" || last == "/" || last == "*"){
        document.getElementById("display").innerHTML = display.substring(0,display.length-1) + "-"
    }
    else if (last == "-") {
        //pass
    }
    else {
        document.getElementById("display").innerHTML += "-"
    }
}

function multiply(){
    let display = document.getElementById("display").innerHTML
    let last = display.charAt(display.length-1)
    if (last == "-" || last == "/" || last == "+"){
        document.getElementById("display").innerHTML = display.substring(0,display.length-1) + "*"
    }
    else if (last == "*") {
        //pass
    }
    else {
        document.getElementById("display").innerHTML += "*"
    }
}

function divide(){
    let display = document.getElementById("display").innerHTML
    let last = display.charAt(display.length-1)
    if (last == "-" || last == "+" || last == "*"){
        document.getElementById("display").innerHTML = display.substring(0,display.length-1) + "/"
    }
    else if (last == "/") {
        //pass
    }
    else {
        document.getElementById("display").innerHTML += "/"
    }
}

function remove(){
    let display = document.getElementById("display").innerHTML
    if (display.length == 1)
    {
        document.getElementById("display").innerHTML = "0"
    }
    else{
        document.getElementById("display").innerHTML = display.substring(0,display.length-1)
    }
}

function reset() {
    document.getElementById("display").innerHTML = "0"
}

function clears() {
    let display = document.getElementById("display").innerHTML
    let p = display.lastIndexOf("+")
    let m = display.lastIndexOf("-")
    let m_p = display.lastIndexOf("*")
    let d = display.lastIndexOf("/")
    console.log(p)
    if (p != -1 && (p > m || m == -1) && (p > m_p || m_p == -1) && (p > d || d == -1))
    {
        document.getElementById("display").innerHTML = display.substring(0,p+1)
    }
    else if (m != -1 && (m > p || p == -1) && (m > m_p || m_p == -1) && (m > d || d == -1))
    {
        document.getElementById("display").innerHTML = display.substring(0,m+1)
    }
    else if (m_p != -1 && (m_p > p || p == -1) && (m_p > m || m == -1) && (m_p > d || d == -1))
    {
        document.getElementById("display").innerHTML = display.substring(0,m_p+1)
    }
    else if (d != -1 && (d > p || p == -1) && (d > m_p || m_p == -1) && (d > m || m == -1))
    {
        document.getElementById("display").innerHTML = display.substring(0,d+1)
    }
}

function equals(){
    let display = document.getElementById("display").innerHTML
    document.getElementById("display").innerHTML = eval(display)
}