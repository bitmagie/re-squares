/** Internal styles */

let backgroundColor = "#000";

let css = {j|
  html,
  body {
    padding:0;
      margin: 0;
      overflow: hidden;
      height: 100%;      
      width:100%;
  }
  canvas{
      background-color:$backgroundColor;
  }

  /* Scale canvas with resize attribute to full size */
  canvas[resize] {
    width: 100%;
    height: 100%;
  }
|j};



let humanColor = "#ff9a00";
let aiColor = "#bfdbe7";

let timeColor = "#ffcc00"; 
let movesColor= "#40e3ff";


let boardBackgroundColor = "#333";
let boardBackgroundStrokeColor = "#2b2200";
let boardMargin = 16.;
let boardBackgroundStrokeWidth = boardMargin;
let backgroundCornerRadius = Paper.Size.create(12.0, 12.0);


let boardLabelColor = "#ffcc00";
let boardLabelFontSize = 10.;

let fieldStrokeColor = "#574400";//"#6d5720";
let fieldStrokeWidth = 0.8;
let fieldCornerRadius = Paper.Size.create(0.0, 0.0);
let fieldFillColor = "#222";
let fieldHighlightColor = "#252525";

let pieceRadiusFactor = 0.6;
let pieceStrokeWidth = 2.0;
let pieceStrokeColor = "#000";
let pieceGradientOffset = 1.3;

let displayPortraitHeight = 80.;
let displayLandscapeWidth = 160.;
let displayStyling =
  Styling.styleDescription(
    ~fillColor=backgroundColor,
    (),
  );

let displayItemHeight = 10.;
let displayItemWidth = 70.;

let resultColors = [|"#DB0E00", "#9D00E0", "#00AD2F", "#A100DB", "#0078E0"|];

let overlayPathStyle = Styling.styleDescription(~fillColor="#6707FA", ());
let gameOverFillColor="#FA9920";
let winMessageFillColor="#B51415";
let newGameFillColor="#7BFA20";
let buttonStrokeColor="#14B7FA";
let buttonFillColor = "#6707FA";

let winMessageFontSize=65.;
let winMessageFontWeight="bold";
let winMessageJustification="center";

let buttonWidth=190.;
let buttonHeight=60.;
let buttonCornerRadius=5.;
let buttonStrokeWidth=5.0;   