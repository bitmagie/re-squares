module DisplayItem: {
  type t = Paper.CompoundPath.t;

  let setPosition: (t, BasicTypes.Point.t) => t;
  let addPosition: (Paper.CompoundPath.t, BasicTypes.Point.t, float) => t;

  let make: (~color:string, ~title:string, ~value:string) => t;

} = {
    
type t = Paper.CompoundPath.t;

let makeTextPath = (~point, ~fillColor,~fontSize,~fontWeight,~justification,~content) => {
      point
      ->PointText.pointTextDescription(
          ~point=_,
          ~fillColor=fillColor,
          ~fontSize=fontSize,
          ~fontWeight = fontWeight,
          ~content=content,            
          ~justification=justification,
          (),
        )
        ->PointText.createFromObject(_);      
    };

let make = (~color:string, ~title:string, ~value:string) => {
    let makeTitle = makeTextPath(~fillColor=color,~fontSize=Styles.displayItemHeight/.2.,~justification="left");
    let makeValue = makeTextPath(~fillColor=color,~fontSize=2.*.Styles.displayItemHeight,~justification="left");
    let description:Paper.CompoundPath.descriptionPointText = Paper.CompoundPath.descriptionPointText(
        ~children=[|          
          BasicTypes.Point.create(0.,0.) ->  
          makeTitle(~point=_,~content=title,~fontWeight="normal"),         
          BasicTypes.Point.create(0.,Styles.displayItemHeight+.10.) ->  
          makeValue(~point=_,~content=value,~fontWeight="normal"),
        |],
        ()
        );
    Paper.CompoundPath.createPointText(description);
};

let setPosition = (item:Paper.CompoundPath.t, position:BasicTypes.Point.t) => {
     item.position = position;
    item;
};

let addPosition = (item:Paper.CompoundPath.t, vector:BasicTypes.Point.t, times:float) => {     
    item.position = vector->Paper.Point.multiply(times) -> BasicTypes.Point.addPoint(item.position);
    item;
};

};

module Display: {
  type t = {
    path: Paper.Path.t,
    mutable player1: (int, Paper.CompoundPath.t),
    mutable time: (int, Paper.CompoundPath.t),
    mutable player2: (int, Paper.CompoundPath.t),
    mutable moves: (int,int, Paper.CompoundPath.t),
    mutable blinkCount: int
  };
  
  type playerScore = | Human(int) | AI(int) | Ghost;
  
  let make: (Paper.Point.t, Layout.format) => t;
  let addScore: (option(t), playerScore) => unit;
  let blink: (option(t), playerScore) => unit;
  let timeTick: (~display: option(t)) => unit;
  let timeReset: (option(t)) => unit;
  let moveTick: (~display: option(t)) => unit;
  let moveReset: (~display: option(t), ~maxMoves: int ) => unit;


} = {
  type t = {
  path: Paper.Path.t,
  mutable player1: (int, Paper.CompoundPath.t),
  mutable time: (int, Paper.CompoundPath.t),
  mutable player2: (int, Paper.CompoundPath.t),
  mutable moves: (int,int, Paper.CompoundPath.t),
  mutable blinkCount: int
};

type playerScore = | Human(int) | AI(int) | Ghost;

let intToString = (~integer: int, ~width: int) => {
  let s = string_of_int(integer);
  let n = String.length(s);
  let trailingZeros = width - n;
  if (trailingZeros > 0) {
    String.make(trailingZeros, '0') ++ s;
  } else {
    s;
  };
};

let intToScoreString = integer => {
  intToString(~integer, ~width=3);
};

let intToTimeString = integer => {
  let s = integer mod 600;
  let mm = s / 60;
  let ss = s - mm * 60;

  let intToTimeSegment = intToString(~width=2);

  intToTimeSegment(~integer=mm) ++ ":" ++ intToTimeSegment(~integer=ss);
};
let movesToText = (remaining, moves) =>
  string_of_int(remaining) ++ " / " ++ intToString(~integer=moves, ~width=3);

let displayStyling = Styling.styleDescription(~fillColor="#000", ());

let setPosition = (path: Paper.Path.t, position: BasicTypes.Point.t) => {
  path.position = position;
  path;
};

let make = (position: Paper.Point.t, format: Layout.format) => {
  let (rectangle,  height, size) =
    switch (format) {
    | Landscape(width, height) => (
        BasicTypes.Rectangle.create(
          0.,
          0.,
          Styles.displayLandscapeWidth,
          Styles.displayItemHeight,
        ),
        height,
        BasicTypes.Size.create(width, height),
      )
    | Portrait(width, height) => (
        BasicTypes.Rectangle.create(
          0.,
          0.,
          Styles.displayItemWidth,
          Styles.displayItemHeight,
        ),
        height,
        BasicTypes.Size.create(width, height),
      )
    };

  let path =
    Paper.Point.create(0., 0.)
    ->Paper.Path.rectangleFromPoint(size)
    ->Paper.Path.setStyle(~path=_, ~style=displayStyling)
    ->setPosition(position);

  let (itemStartPosition, offset) =
    switch (format) {
    | Landscape(_, _) => (
        BasicTypes.Point.create(
          path.position.x,
          path.position.y -. height /. 2. +. Styles.displayItemHeight,
        ),
        BasicTypes.Point.create(0., 4.5 *. Styles.displayItemHeight),
      )
    | Portrait(width, _) => (
        BasicTypes.Point.create(
          path.position.x -. width /. 2. +. 2. *. Styles.boardMargin,
          path.position.y,
        ),
        BasicTypes.Point.create(width /. 4., 0.),
      )
    };

  {
    path,
    player1: (
      0,
      DisplayItem.make(
        ~color=Styles.humanColor,
        ~title="PLAYER",
        ~value="1 000",
      )
      ->DisplayItem.setPosition(itemStartPosition),
    ),

    player2: (
      0,
      DisplayItem.make(
        ~color=Styles.aiColor,
        ~title="PLAYER",
        ~value="2 000",
      )
      ->DisplayItem.setPosition(itemStartPosition)
      ->DisplayItem.addPosition(offset, 1.),
    ),
    time: (
      0,
      DisplayItem.make(
        ~color=Styles.timeColor,
        ~title="TIME",
        ~value="00:00",
      )
      ->DisplayItem.setPosition(itemStartPosition)
      ->DisplayItem.addPosition(offset, 2.),
    ),
    moves: (
      0,
      0,
      DisplayItem.make(
        ~color=Styles.movesColor,
        ~title="MOVES",
        ~value="00/00",
      )
      ->DisplayItem.setPosition(itemStartPosition)
      ->DisplayItem.addPosition(offset, 3.),
    ),
    blinkCount: 0
  };
};

let timeTick = (~display: option(t)) => {
  switch (display) {
  | Some(display) =>
    let (seconds, path) = display.time;
    let children = Paper.CompoundPath.getPointextChildren(path);
    children[1].content = intToTimeString(seconds + 1);

    display.time = (seconds + 1, path);
    ();
  | _ => ()
  };
};

let timeReset = (display) => {
  switch (display) {
  | Some(display) =>
    let (_, path) = display.time;
    let children = Paper.CompoundPath.getPointextChildren(path);
    children[1].content = intToTimeString(0);

    display.time = (0, path);
    ();
  | _ => ()
  };
};

let blink = (display, playerScore) => {  
  switch (display) {
  | Some(display) =>{
    let (_,player1Path) = display.player1;
    let (_,player2Path) = display.player2;
    switch(playerScore){
      |Human(_) => {
        player2Path.opacity = 1.0;
        let opacity = switch (player1Path.opacity) {
          | 1.0 => 0.0
          | _ => 1.0
        };
        player1Path.opacity = opacity;
      }
      |AI(_) => {
        player1Path.opacity = 1.0;
        let opacity = switch (player2Path.opacity) {
          | 1.0 => 0.0
          | _ => 1.0
        };
        player2Path.opacity = opacity;
      }
      |_ => {
        player1Path.opacity = 1.0;
        player2Path.opacity = 1.0;
      }
    };
    ();
  }
    | _ => ()
  };
  
};

 let moveTick = (~display: option(t)) => {
  switch (display) {
  | Some(display) =>
    let (remaining, moves, path) = display.moves;
    let newRemaining = remaining +1 ;
    let newContent = intToString(~integer=newRemaining,~width=2) ++"/" ++           
    intToString(~integer=moves,~width=2);           
    
    let children = Paper.CompoundPath.getPointextChildren(path);
    children[1].content = newContent;

    display.moves = (newRemaining, moves, path);
    ();
  | _ => ()
  };
};

let moveReset = (~display: option(t), ~maxMoves: int ) => {
  switch (display) {
  | Some(display) =>
    let (_, _, path) = display.moves;
    
    let newContent = intToString(~integer=0,~width=2) ++"/" ++           
    intToString(~integer=maxMoves,~width=2);           
    
    let children = Paper.CompoundPath.getPointextChildren(path);
    children[1].content = newContent;

    display.moves = (0, maxMoves, path);
    ();
  | _ => ()
  };
};

let addScore = (display, playerScore) => {
    switch(display){
      |Some(display) => {
          switch(playerScore){
          | Human(score) => {
                let (hiScore,path) = display.player1;
                let newScore = hiScore + score;
              
              let newContent = "1 " ++ intToString(~integer=newScore, ~width=3);
              let children = Paper.CompoundPath.getPointextChildren(path);
              children[1].content = newContent;

              display.player1 = (newScore,path);
               
                ();
          }
          | AI(score) => {
                let (hiScore,path) = display.player2;
                let newScore = hiScore + score;
              
              let newContent = "2 " ++ intToString(~integer=newScore, ~width=3);
              let children = Paper.CompoundPath.getPointextChildren(path);
              children[1].content = newContent;

              display.player2 = (newScore,path);
               
                ();
          }
          | _ => ();
        };
         
        ();
      }
      | _ => ()
    };
    
    ();
  };  
};
module Piece:{ 
  type t = Paper.CompoundPath.t;
  let make: (
        ~color: Styling.cssColor,
        ~position: Paper.Point.t,
        ~size: Paper.size,
        ~gradientOffset: float,
      ) => t;


} = {
    type t = Paper.CompoundPath.t;

let make = (
        ~color: Styling.cssColor,
        ~position: Paper.Point.t,
        ~size: Paper.size,
        ~gradientOffset: float,
      ) => {
    let radius = min(size.width, size.height) *. Styles.pieceRadiusFactor /. 2.;
   
    let gradient = Paper.Gradient.create((color, "black"), true);

    let description =
      Paper.CompoundPath.descriptionObject(
        ~children=[|
          Paper.Point.create(0., 0.)->Paper.Path.circle(radius),
          Paper.Point.create(radius /. 8., radius /. 8.)
          ->Paper.Path.circle(radius /. 3.),
        |],
        ~fillColor=
          Paper.Color.createGradient(
            ~gradient,
            ~origin=Paper.Point.create(0., 0.),
            ~destination=
              Paper.Point.create(radius *. gradientOffset, radius *. gradientOffset),
            ~highlight=Paper.Point.create(radius /. 4., radius /. 4.),
            (),
          ),
        (),
      );

    let piece = Paper.CompoundPath.create(description);

    piece.position = position;

    piece;
  };
};

module Field:{
   type t = {
      path: Paper.Path.t,
      piece: option(Piece.t)
    };

  let make:
    (
      ~position: Paper.Point.t,
      ~fieldSize: Paper.Size.t,
      ~style: Paper.styleDescription,
      ~cornerRadius: Paper.Size.t,
    ) => Paper.Path.t;
} = {
    type t = {
      path: Paper.Path.t,
      piece: option(Piece.t)
    };

let make =
    (
      ~position: Paper.Point.t,
      ~fieldSize: Paper.Size.t,
      ~style: Paper.styleDescription,
      ~cornerRadius: Paper.Size.t,
    ) => {
  Paper.Rectangle.createFromPoint(position, fieldSize)
  ->Paper.Path.rectangle(_, ~radius=cornerRadius, ())
  ->Paper.Path.setStyle(~path=_, ~style);
};


};

module Board:{
  type t = {
    fieldsPerSide: int,
    fieldSize: Paper.Size.t,
    fields: array(array(option(Field.t))),
    originDistance: Paper.Point.t,
    mutable disabled: bool,
    display: option(Display.t),
  };

  let make: (~position: Paper.Point.t, ~format: Layout.format) => t;
  let getFieldCoordinatesFromBoardPosition: (t, Paper.Point.t) => option((int, int));
  let setPiece: (t, Position.t , string) => unit;

  let showResult: (t, SquarePattern.t, int) => unit;


} = {
    

let boardRowLabel = "123456789JKLMNOPQRSTUVWXYZ";
let boardColLabel = "abcdefghijklmnopqrstuvwxyz";

type t = {
  fieldsPerSide: int,
  fieldSize: Paper.Size.t,
  fields: array(array(option(Field.t))),
  originDistance: Paper.Point.t,
  mutable disabled: bool,
  display: option(Display.t),
};

exception OutOfRange(string);

let onMouseLeaveHandler = (event: MouseEvent.t) => {
  switch (Js.Nullable.toOption(event.target)) {
  | Some(target) =>
    target.style = Styling.styleDescription(~fillColor=Styles.fieldFillColor, ())
  | _ => ()
  };
};

let onMouseEnterHandler = (event: MouseEvent.t) => {
  switch (Js.Nullable.toOption(event.target)) {
  | Some(target) =>
    target.style =
      Styling.styleDescription(~fillColor=Styles.fieldHighlightColor, ())
  | _ => ()
  };
};

let isOutOfBounds = (i, dim) => {
  switch (i) {
  | i when i < 0 || i >= dim => true
  | _ => false
  };
};

let getFieldCoordinatesFromBoardPosition =
    (board: t, position: Paper.Point.t): option((int, int)) => {
  let size = Paper.Point.createFromSize(board.fieldSize);
  let coordinates =
    position
    ->Paper.Point.subtractPoint(board.originDistance)
    ->Paper.Point.dividePoint(size);
  let (i,j) =  (
    int_of_float(Js.Math.round(coordinates.x)),
    int_of_float(Js.Math.round(coordinates.y)),
  );
  let dim = Layout.fieldsPerSide;
  switch (i, j) {
  | (i, _) when isOutOfBounds(i, dim) => None
  | (_, j) when isOutOfBounds(j, dim) => None
  | (_, _) => Some((i,j))
  };

};

let getBoardPositionFromFieldCoordinates = (board: t, coordinates: (int, int)) => {
  let (i, j) = coordinates;
  Some(Paper.Point.create(
    float_of_int(i) *. board.fieldSize.width,
    float_of_int(j) *. board.fieldSize.height,
  )
  ->Paper.Point.addPoint(board.originDistance));
};



let getField = ( (i, j), board): option(Field.t) => {
  let dim = Layout.fieldsPerSide;
  switch (i, j) {
  | (i, _) when isOutOfBounds(i, dim) => None
  | (_, j) when isOutOfBounds(j, dim) => None
  | (_, _) => board.fields[i][j]
  };
};

let setPiece = (board, position , color): unit => {
  let dim = Layout.fieldsPerSide;
  let (i,j) = position;      
  switch (i, j) {
    | (i, _) when isOutOfBounds(i, dim) => ()
    | (_, j) when isOutOfBounds(j, dim) => ()
    | (_, _) => {
      let field = board.fields[i][j];
      switch (field) {
        | Some(field) =>
          let position = field.path.position;
          let width = field.path.strokeBounds.width;
          let height = field.path.strokeBounds.height;
          let size = Paper.Size.create(width, height);

          let piece = Piece.make(~color, ~position, ~size, ~gradientOffset=Styles.pieceGradientOffset);
          board.fields[i][j] = Some({...field, piece: Some(piece)});
          ();
        | _ => ()
      };  
    };  
  };  
};


let make = (~position: Paper.Point.t, ~format: Layout.format) => {

  let length =
    (
      switch (format) {
      | Landscape(_, height) => height
      | Portrait(width, _) => width
      }
    )
    -. Styles.boardMargin;

  
  let displayVisible =switch (format) {
    | Landscape(width, _) =>
      width -. length -. Styles.boardMargin -. Styles.displayLandscapeWidth >= 0.
    | Portrait(_, height) => 
      height -. length -. Styles.boardMargin -. Styles.displayPortraitHeight >= 0.

    };

  let displayFormat: Layout.format =
    switch (format) {
    | Landscape(_, _) =>
      Landscape(Styles.displayLandscapeWidth, length-. Styles.boardMargin)
    | Portrait(_, _) => Portrait(length-. Styles.boardMargin, Styles.displayPortraitHeight)
    };

  let (boardPosition, displayPosition) =
    switch (format) {
    | Landscape(_, height) when displayVisible => (
        position->Paper.Point.addPoint(
          Paper.Point.create(Styles.displayLandscapeWidth /. 2., 0.),
        ),
        position->Paper.Point.subtractPoint(
          Paper.Point.create(height /. 2., 0.),
        ),
      )
    | Portrait(width, _) when displayVisible => (
        Paper.Point.create(width /. 2., Styles.displayPortraitHeight /. 2.)
        ->Paper.Point.addPoint(
            Paper.Point.create(0., (length +. Styles.boardMargin +. Styles.displayPortraitHeight) /. 2.),
          ),
        position
        ->Paper.Point.multiplyPoint(Paper.Point.create(1., 0.))
        ->Paper.Point.addPoint(Paper.Point.create(0., Styles.displayPortraitHeight /. 2.)),
      )
    | _ => (position, Paper.Point.create(0., 0.))
    };

  let display =
    switch (displayVisible) {
    | true => Some(Display.make(displayPosition, displayFormat))
    | false => None
    };

  let maxMoves = Layout.fieldsPerSide*Layout.fieldsPerSide;
  Display.moveReset(~display=display, ~maxMoves=maxMoves);
  
  let outOfRangeExn =OutOfRange("Layout.fieldsPerSide <= 0");
  let n =
    switch (Layout.fieldsPerSide) {
    | n when n > 0 => n
    | _ => raise(outOfRangeExn)
    };

  let boardSize = Paper.Size.create(length, length);

  let backgroundStyle =
    Styling.styleDescription(
      ~fillColor=Styles.boardBackgroundColor,
      ~strokeWidth=Styles.boardBackgroundStrokeWidth,
      ~strokeColor=Styles.boardBackgroundStrokeColor,
      (),
    );

  let backgroundPath =
    //Paper.Point.create(0., 0.)->Paper.Path.rectangleFromPoint(boardSize);
    Paper.Point.create(0., 0.)
    ->Paper.Rectangle.createFromPoint(boardSize)
    ->Paper.Path.rectangle(_, ~radius=Styles.backgroundCornerRadius, ())
    ->Paper.Path.setStyle(~path=_, ~style=backgroundStyle);

  let offsetVector =
    boardPosition->Paper.Point.subtractPoint(backgroundPath.position);
  ignore(
    backgroundPath.position =
      Paper.Point.addPoint(backgroundPath.position, offsetVector),
  );

  let fieldSideLength = (length -. Styles.boardMargin) /. float_of_int(n);

  let fieldSize = Paper.Size.create(fieldSideLength, fieldSideLength);

  let fieldOffset = Styles.boardMargin /. 2.;

  let fieldStyle =
    Paper.styleDescription(
      ~strokeColor=Styles.fieldStrokeColor,
      ~fillColor=Styles.fieldFillColor,
      ~strokeWidth=Styles.fieldStrokeWidth,
      (),
    );

  let fieldArray: array(array(option(Field.t))) =
    Array.make_matrix(n, n, None);

  for (i in 0 to n - 1) {
    for (j in 0 to n - 1) {
      fieldArray[i][j] =
        Some({
          path:
            Paper.Point.create(
              float_of_int(i) *. fieldSideLength +. fieldOffset,
              float_of_int(j) *. fieldSideLength +. fieldOffset,
            )
            ->Paper.Point.addPoint(offsetVector)
            ->Field.make(
                ~position=_,
                ~fieldSize,
                ~style=fieldStyle,
                ~cornerRadius=Styles.fieldCornerRadius,
              ),
          piece: None
        });

      switch (fieldArray[i][j]) {
      | Some(item) =>
        Paths.Path.setOnMouseLeave(item.path, onMouseLeaveHandler);
        Paths.Path.setOnMouseEnter(item.path, onMouseEnterHandler);
      | _ => ()
      };
    };
  };

  let getLabel = (idx, labelString) => {
    let n = String.length(labelString);
    if (idx < n) {
      String.sub(labelString, idx, 1);
    } else {
      "";
    };
  };

  let setBoardLabel =
      (~label, ~fieldOption: option(Field.t), ~direction, ~offset, ~color) => {
    switch (fieldOption) {
    | Some(field) =>
      let pathPosition = Paper.Point.createFromPoint(field.path.position);

      ignore(offset
      ->Paper.Point.multiply(direction)
      ->Paper.Point.addPoint(pathPosition)
      ->PointText.pointTextDescription(
          ~point=_,
          ~fillColor=color,
          ~fontSize=Styles.boardLabelFontSize,
          ~content=label,
          ~justification="center",
          (),
        )
      ->PointText.createFromObject(_));
      ();
    | _ => ()
    };
  };

  let dist = (fieldSideLength +. Styles.boardBackgroundStrokeWidth) /. 2.;

  let rowOffset = Paper.Point.create(dist, 0.);

  let colOffset = Paper.Point.create(0., dist);

  for (idx in 0 to n - 1) {
    setBoardLabel(
      ~label=getLabel(n - 1 - idx, boardRowLabel),
      ~fieldOption=fieldArray[0][idx],
      ~direction=-1.0,
      ~offset=rowOffset,
      ~color=Styles.boardLabelColor,
    );
    setBoardLabel(
      ~label=getLabel(n - 1 - idx, boardRowLabel),
      ~fieldOption=fieldArray[n - 1][idx],
      ~direction=1.0,
      ~offset=rowOffset,
      ~color=Styles.boardLabelColor,
    );
    setBoardLabel(
      ~label=getLabel(idx, boardColLabel),
      ~fieldOption=fieldArray[idx][0],
      ~direction=-1.0,
      ~offset=colOffset,
      ~color=Styles.boardLabelColor,
    );
    setBoardLabel(
      ~label=getLabel(idx, boardColLabel),
      ~fieldOption=fieldArray[idx][n - 1],
      ~direction=1.0,
      ~offset=colOffset,
      ~color=Styles.boardLabelColor,
    );
  };

  let originDistance =
    switch (fieldArray[0][0]) {
    | Some(item) => Paper.Point.clone(item.path.position)
    | _ => Paper.Point.create(0., 0.)
    };

  {
    fieldsPerSide: n,
    fieldSize,
    fields: fieldArray,
    originDistance,
    disabled: false,
    display,
  };
};

let disable = (~board: t) => {
  board.disabled = true;
};

let enable = (~board: t) => {
  board.disabled = false;
};


let removePiece = (fieldOption: option(Field.t)) => {
  switch (fieldOption) {
  | Some(field) =>
    ignore(
      switch (field.piece) {
      | Some(piece) => Paper.CompoundPath.remove(piece)       
      | _ => false
      },
    );
    Some({...field, piece: None});
  | _ => None
  };
};

let removePieceFromField = (~board: t, ~fieldCoordinates: (int, int)): unit => {
  let (i, j) = fieldCoordinates;
  board.fields[i][j] = fieldCoordinates->getField(board)->removePiece(_);
};

let clear = (~board: t) => {
  for (i in 0 to Layout.fieldsPerSide - 1) {
    for (j in 0 to Layout.fieldsPerSide - 1) {
      removePieceFromField(~board, ~fieldCoordinates=(i, j));
    };
  };
  ();
};

let isOutOfRange = (point: Paper.Point.t) => {
  let dim = float_of_int(Layout.fieldsPerSide - 1);
  point.x < 0. || point.x > dim || point.y < 0. || point.y > dim;
};


let resultColors = Styles.resultColors;

let showResult = (board, resultSquare:SquarePattern.t, len) => { 
    
  let p0 = getBoardPositionFromFieldCoordinates(board,resultSquare.p0);
  let p1 = getBoardPositionFromFieldCoordinates(board,resultSquare.p1);
  let p2 = getBoardPositionFromFieldCoordinates(board,resultSquare.p2);
  let p3 = getBoardPositionFromFieldCoordinates(board,resultSquare.p3);
  
  let i = Js.Math.abs_int(len) mod Array.length(Styles.resultColors);
  let color = Styles.resultColors[i];
  let resultStyle =
    Paper.styleDescription(
      ~strokeColor=color,
      ~strokeWidth=2.0,
      ~dashArray=[|5., 20.|],
      (),
    );
    switch(p0,p1,p2,p3){
      |(Some(p0),Some(p1),Some(p2),Some(p3)) => 
      Paper.Path.line(p0, p1)
      ->Paper.Path.setStyle(~path=_, ~style=resultStyle);
      Paper.Path.line(p1, p2)
      ->Paper.Path.setStyle(~path=_, ~style=resultStyle);
      Paper.Path.line(p2, p3)
      ->Paper.Path.setStyle(~path=_, ~style=resultStyle);
      Paper.Path.line(p3, p0)
      ->Paper.Path.setStyle(~path=_, ~style=resultStyle);

      PointText.pointTextDescription(
        ~point=p0->Paper.Point.addPoint(p2)->Paper.Point.divide(2.),
        ~fillColor=color,
        ~fontSize=65.,
        ~content=string_of_int(resultSquare.score),
        ~justification="center",
        (),
      )
      ->PointText.createFromObject(_);
      ();
    | _ => ();      
    }; 
};

};

type t = Board.t;
type playerScore = Display.playerScore = | Human(int) | AI(int) | Ghost;

let init = Board.make; 
let getFieldCoordinatesFromMousePosition = Board.getFieldCoordinatesFromBoardPosition;
let timeTick = (renderer:t) => Display.timeTick(~display=renderer.display);
let timeReset = (renderer:t) => Display.timeReset(renderer.display);
let blink = (renderer:t, playerScore) => Display.blink(renderer.display,playerScore);
let addScore = (renderer:t, playerScore) => Display.addScore(renderer.display,playerScore);
let setPiece = (renderer, position, color) => renderer->Board.setPiece(position, color);
let moveTick = (renderer:t) => Display.moveTick(~display=renderer.display);
let showResult = (renderer,square,resultLength) => renderer->Board.showResult(square,resultLength);