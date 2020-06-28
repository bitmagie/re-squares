module rec Segment: {
  type point = BasicTypes.point;
  type t = {
    point: BasicTypes.point,
    handleIn: BasicTypes.point,
    handleOut: BasicTypes.point,
    selected: bool,
    index: int,
    path: Path.t,
  };
  type segment = t;

  [@bs.module "paper"] [@bs.new]
  external create:
    (point, ~handleIn: point=?, ~handleOut: point=?, unit) => segment =
    "Segment";

  [@bs.set] external handleIn: (segment, point) => unit = "handleIn";
  [@bs.set] external handleOut: (segment, point) => unit = "handleOut";

  [@bs.send] external remove: t => bool = "remove";
} = {
  type point = BasicTypes.point;
  type t = {
    point: BasicTypes.point,
    handleIn: BasicTypes.point,
    handleOut: BasicTypes.point,
    selected: bool,
    index: int,
    path: Path.t,
  };
  type segment = t;

  [@bs.module "paper"] [@bs.new]
  external create:
    (point, ~handleIn: point=?, ~handleOut: point=?, unit) => segment =
    "Segment";

  [@bs.set] external handleIn: (segment, point) => unit = "handleIn";
  [@bs.set] external handleOut: (segment, point) => unit = "handleOut";

  [@bs.send] external remove: t => bool = "remove";
}
and Path: {
  type t = {
    segments: array(Segment.t),
    firstSegment: Segment.t,
    lastSegment: Segment.t,
    curves: array(Curve.t),
    firstCurve: Curve.t,
    lastCurve: Curve.t,
    mutable closed: bool,
    length: float,
    area: float,
    fullySelected: bool,
    id: float,
    className: string,
    name: string,
    mutable style: Styling.styleDescription,
    mutable locked: bool,
    mutable visible: bool,
    mutable blendMode: string,
    mutable opacity: float,
    mutable selected: bool,
    mutable clipMask: bool,
    mutable position: BasicTypes.point,
    mutable pivot: BasicTypes.point,
    mutable rotation: float,
    bounds: BasicTypes.rectangle,
    strokeBounds: BasicTypes.rectangle,
    internalBounds: BasicTypes.rectangle,
    mutable applyMatrix: bool,
    mutable strokeColor: Styling.Color.t,
    mutable strokeWidth: float,
    mutable fillColor: Styling.Color.t,
  };
  type path = t;
  type resultPath = t;
  type pathData = string;
  type number = float;
  type points = float;
  type sides = float;
  type radius = float;
  type radius1 = float;
  type radius2 = float;
  type size = BasicTypes.size;
  type rounding = BasicTypes.size;
  type topLeft = BasicTypes.point;
  type from = BasicTypes.point;
  type through = BasicTypes.point;
  type to_ = BasicTypes.point;
  type center = BasicTypes.point;
  type hexValue = string;
  type rectangle = BasicTypes.rectangle;
  type angle = float;
  type index = int;

  type eventHandler = MouseEvent.t => unit;

  [@bs.module "paper"] [@bs.new]
  external create: (~segments: array(Segment.t)=?, unit) => Path.t = "Path";

  [@bs.module "paper"] [@bs.new]
  external createFromString: pathData => path = "Path";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external line: (from, to_) => path = "Line";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external circle: (center, radius) => path = "Circle";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external rectangle: (rectangle, ~radius: size=?, unit) => path = "Rectangle";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external rectangleFromPoint: (topLeft, size) => path = "Rectangle";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external rectangleFromPoints: (from, to_) => path = "Rectangle";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external ellipse: (rectangle, ~radius: size=?, unit) => path = "Ellipse";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external arc: (from, through, to_) => path = "Arc";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external regularPolygon: (center, sides, radius) => path = "RegularPolygon";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external star: (center, points, radius1, radius2) => path = "Star";

  [@bs.send] external removeOnMove: path => unit = "removeOnMove";

  [@bs.set] external setStrokeColor: (path, hexValue) => unit = "strokeColor";
  [@bs.set] external setStrokeWidth: (path, number) => unit = "strokeWidth";

  [@bs.send] external add: (path, BasicTypes.point) => unit = "add";
  [@bs.send]
  external addPoints: (path, BasicTypes.point, BasicTypes.point) => unit =
    "add";
  [@bs.send] external addArray: (path, (float, float)) => unit = "add";
  [@bs.send] external addSegment: (path, Segment.t) => unit = "add";
  [@bs.send] external addSegments: (path, array(Segment.t)) => unit = "add";

  [@bs.send]
  external insert: (path, index, BasicTypes.point) => unit = "insert";
  [@bs.send]
  external insertSegment: (path, index, Segment.t) => unit = "insert";
  [@bs.send]
  external insertSegments: (path, index, array(Segment.t)) => unit = "insert";

  [@bs.send] external removeSegment: (path, index) => unit = "removeSegment";
  [@bs.send]
  external removeSegments: (path, ~fom: index=?, ~to_: index=?, unit) => unit =
    "removeSegments";

  [@bs.send]
  external translate: (path, BasicTypes.point) => unit = "translate";
  [@bs.send]
  external rotate: (path, angle, ~center: center=?, unit) => unit = "rotate";

  [@bs.set]
  external setOnMouseDown: (path, eventHandler) => unit = "onMouseDown";
  [@bs.set]
  external setOnMouseDrag: (path, eventHandler) => unit = "onMouseDrag";
  [@bs.set] external setOnMouseUp: (path, eventHandler) => unit = "onMouseUp";
  [@bs.set] external setOnClick: (path, eventHandler) => unit = "onClick";
  [@bs.set]
  external setOnMouseMove: (path, eventHandler) => unit = "onMouseMove";
  [@bs.set]
  external setOnMouseEnter: (path, eventHandler) => unit = "onMouseEnter";
  [@bs.set]
  external setOnMouseLeave: (path, eventHandler) => unit = "onMouseLeave";

  [@bs.send] external remove: t => bool = "remove";

  let setStyle: (~path: path, ~style: Styling.styleDescription) => path;
} = {
  type t = {
    segments: array(Segment.t),
    firstSegment: Segment.t,
    lastSegment: Segment.t,
    curves: array(Curve.t),
    firstCurve: Curve.t,
    lastCurve: Curve.t,
    mutable closed: bool,
    length: float,
    area: float,
    fullySelected: bool,
    id: float,
    className: string,
    name: string,
    mutable style: Styling.styleDescription,
    mutable locked: bool,
    mutable visible: bool,
    mutable blendMode: string,
    mutable opacity: float,
    mutable selected: bool,
    mutable clipMask: bool,
    mutable position: BasicTypes.point,
    mutable pivot: BasicTypes.point,
    mutable rotation: float,
    bounds: BasicTypes.rectangle,
    strokeBounds: BasicTypes.rectangle,
    internalBounds: BasicTypes.rectangle,
    mutable applyMatrix: bool,
    mutable strokeColor: Styling.Color.t,
    mutable strokeWidth: float,
    mutable fillColor: Styling.Color.t,
  };
  type path = t;
  type resultPath = t;
  type pathData = string;
  type number = float;
  type points = float;
  type sides = float;
  type radius = float;
  type radius1 = float;
  type radius2 = float;
  type size = BasicTypes.size;
  type rounding = BasicTypes.size;
  type topLeft = BasicTypes.point;
  type from = BasicTypes.point;
  type through = BasicTypes.point;
  type to_ = BasicTypes.point;
  type center = BasicTypes.point;
  type hexValue = string;
  type rectangle = BasicTypes.rectangle;
  type angle = float;
  type index = int;

  type eventHandler = MouseEvent.t => unit;

  [@bs.module "paper"] [@bs.new]
  external create: (~segments: array(Segment.t)=?, unit) => Path.t = "Path";

  [@bs.module "paper"] [@bs.new]
  external createFromString: pathData => path = "Path";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external line: (from, to_) => path = "Line";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external circle: (center, radius) => path = "Circle";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external rectangle: (rectangle, ~radius: size=?, unit) => path = "Rectangle";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external rectangleFromPoint: (topLeft, size) => path = "Rectangle";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external rectangleFromPoints: (from, to_) => path = "Rectangle";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external ellipse: (rectangle, ~radius: size=?, unit) => path = "Ellipse";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external arc: (from, through, to_) => path = "Arc";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external regularPolygon: (center, sides, radius) => path = "RegularPolygon";
  [@bs.module "paper"] [@bs.scope "Path"] [@bs.val]
  external star: (center, points, radius1, radius2) => path = "Star";

  [@bs.send] external removeOnMove: path => unit = "removeOnMove";

  [@bs.set] external setStrokeColor: (path, hexValue) => unit = "strokeColor";
  [@bs.set] external setStrokeWidth: (path, number) => unit = "strokeWidth";

  [@bs.send] external add: (path, BasicTypes.point) => unit = "add";
  [@bs.send]
  external addPoints: (path, BasicTypes.point, BasicTypes.point) => unit =
    "add";
  [@bs.send] external addArray: (path, (float, float)) => unit = "add";
  [@bs.send] external addSegment: (path, Segment.t) => unit = "add";
  [@bs.send] external addSegments: (path, array(Segment.t)) => unit = "add";

  [@bs.send]
  external insert: (path, index, BasicTypes.point) => unit = "insert";
  [@bs.send]
  external insertSegment: (path, index, Segment.t) => unit = "insert";
  [@bs.send]
  external insertSegments: (path, index, array(Segment.t)) => unit = "insert";

  [@bs.send] external removeSegment: (path, index) => unit = "removeSegment";
  [@bs.send]
  external removeSegments: (path, ~fom: index=?, ~to_: index=?, unit) => unit =
    "removeSegments";

  [@bs.send]
  external translate: (path, BasicTypes.point) => unit = "translate";
  [@bs.send]
  external rotate: (path, angle, ~center: center=?, unit) => unit = "rotate";

  [@bs.set]
  external setOnMouseDown: (path, eventHandler) => unit = "onMouseDown";
  [@bs.set]
  external setOnMouseDrag: (path, eventHandler) => unit = "onMouseDrag";
  [@bs.set] external setOnMouseUp: (path, eventHandler) => unit = "onMouseUp";
  [@bs.set] external setOnClick: (path, eventHandler) => unit = "onClick";
  [@bs.set]
  external setOnMouseMove: (path, eventHandler) => unit = "onMouseMove";
  [@bs.set]
  external setOnMouseEnter: (path, eventHandler) => unit = "onMouseEnter";
  [@bs.set]
  external setOnMouseLeave: (path, eventHandler) => unit = "onMouseLeave";

  [@bs.send] external remove: t => bool = "remove";

  let setStyle = (~path: path, ~style: Styling.styleDescription) => {
    path.style = style;
    path;
  };
}

and CurveLocation: {
  type t = {
    segment: Segment.t,
    curve: Curve.t,
    path: Path.t,
    index: float,
    time: float,
    point: BasicTypes.point,
    offset: float,
    curveOffset: float,
    intersection: CurveLocation.t,
    tangent: BasicTypes.point,
    normal: BasicTypes.point,
    curvature: float,
    distance: float,
  };
  type curveLocation = t;
  type otherCurveLocation = t;
  type curve = Curve.t;
  type time = float;

  [@bs.module "Paper"] [@bs.new]
  external create:
    (curve, time, ~point: BasicTypes.point=?, unit) => curveLocation =
    "Curve";

  [@bs.send]
  external equals: (curveLocation, otherCurveLocation) => bool = "equals";
  [@bs.send] external toString: curveLocation => string = "toString";

  [@bs.send] external isTouching: curveLocation => bool = "isTouching";
  [@bs.send] external isCrossing: curveLocation => bool = "isCrossing";
  [@bs.send] external hasOverlap: curveLocation => bool = "hasOverlap";
} = {
  type t = {
    segment: Segment.t,
    curve: Curve.t,
    path: Path.t,
    index: float,
    time: float,
    point: BasicTypes.point,
    offset: float,
    curveOffset: float,
    intersection: CurveLocation.t,
    tangent: BasicTypes.point,
    normal: BasicTypes.point,
    curvature: float,
    distance: float,
  };
  type curveLocation = t;
  type otherCurveLocation = t;
  type curve = Curve.t;
  type time = float;

  [@bs.module "Paper"] [@bs.new]
  external create:
    (curve, time, ~point: BasicTypes.point=?, unit) => curveLocation =
    "Curve";

  [@bs.send]
  external equals: (curveLocation, otherCurveLocation) => bool = "equals";
  [@bs.send] external toString: curveLocation => string = "toString";

  [@bs.send] external isTouching: curveLocation => bool = "isTouching";
  [@bs.send] external isCrossing: curveLocation => bool = "isCrossing";
  [@bs.send] external hasOverlap: curveLocation => bool = "hasOverlap";
}
and Curve: {
  type t = {
    point1: BasicTypes.point,
    point2: BasicTypes.point,
    handle1: BasicTypes.point,
    handle2: BasicTypes.point,
    segment1: Segment.t,
    path: Path.t,
    index: float,
    next: Curve.t,
    previous: Curve.t,
    selected: bool,
    values: array(float),
    points: array(BasicTypes.point),
    length: float,
    area: float,
    bounds: BasicTypes.rectangle,
    strokeBounds: BasicTypes.rectangle,
    handleBounds: BasicTypes.rectangle,
  };
  type curve = t;
  type otherCurve = t;
  type resultCurve = t;
  type segment1 = Segment.t;
  type segment2 = Segment.t;

  type point = BasicTypes.point;
  type otherPoint = BasicTypes.point;
  type point1 = BasicTypes.point;
  type point2 = BasicTypes.point;
  type handle1 = BasicTypes.point;
  type handle2 = BasicTypes.point;
  type tangent = BasicTypes.point;
  type normal = BasicTypes.point;
  type curveTimeParameters = array(float);
  type from = float;
  type to_ = float;
  type location = CurveLocation.t;
  type offset = float;
  type time = float;
  type curvature = float;
  type curveLocations = array(location);

  type info;

  [@bs.module "paper"] [@bs.new]
  external create: (segment1, segment2) => curve = "Curve";
  [@bs.module "paper"] [@bs.new]
  external createFromPoints: (point1, handle1, handle2, point2) => curve =
    "Curve";

  [@bs.send] external clone: curve => resultCurve = "clone";
  [@bs.send] external toString: curve => string = "toString";
  [@bs.send] external classify: curve => info = "classify";
  [@bs.send] external remove: curve => bool = "remove";
  [@bs.send] external isFirst: curve => bool = "isFirst";
  [@bs.send] external isLast: curve => bool = "isLast";
  [@bs.send] external getPart: (curve, from, to_) => resultCurve = "isLast";
  [@bs.send] external divideAt: (curve, location) => resultCurve = "divideAt";
  [@bs.send]
  external divideAtOffset: (curve, offset) => resultCurve = "divideAt"; // TODO: handle null
  [@bs.send]
  external divideAtTime: (curve, time) => resultCurve = "divideAtTime"; // TODO: handle null
  [@bs.send] external splitAt: (curve, location) => resultCurve = "splitAt";
  [@bs.send]
  external splitAtOffset: (curve, offset) => resultCurve = "splitAt";
  [@bs.send]
  external splitAtTime: (curve, time) => resultCurve = "splitAtTime";
  [@bs.send] external reversed: curve => resultCurve = "reversed";
  [@bs.send] external clearHandles: curve => unit = "clearHandles";

  [@bs.send] external hasHandles: curve => bool = "hasHandles";
  [@bs.send]
  external hasLength: (curve, ~epsilon: float=?, unit) => bool = "hasLength";
  [@bs.send] external isStraight: curve => bool = "isStraight";
  [@bs.send] external isLinear: curve => bool = "isLinear";
  [@bs.send] external isCollinear: (curve, otherCurve) => bool = "isCollinear";
  [@bs.send] external isHorizontal: curve => bool = "isHorizontal";
  [@bs.send] external isVertical: curve => bool = "isVertical";

  [@bs.send]
  external getLocationAt: (curve, offset) => location = "getLocationAt";
  [@bs.send]
  external getLocationAtTime: (curve, time) => location = "getLocationAtTime";
  [@bs.send]
  external getTimeAt: (curve, offset, ~start: float=?, unit) => time =
    "getTimeAt";
  [@bs.send]
  external getTimesWithTangent: (curve, tangent) => curveTimeParameters =
    "getTimesWithTangent";
  [@bs.send]
  external getOffsetAtime: (curve, time) => offset = "getOffsetAtime";
  [@bs.send]
  external getLocationOf: (curve, point) => location = "getLocationOf";
  [@bs.send] external getOffsetOf: (curve, point) => offset = "getOffsetOf";
  [@bs.send] external getTimeOf: (curve, point) => time = "getTimeOf";
  [@bs.send]
  external getNearestLocation: (curve, point) => location =
    "getNearestLocation";
  [@bs.send]
  external getNearestPoint: (curve, point) => otherPoint =
    "getNearestBasicTypes.point";
  [@bs.send]
  external getPointAt: (curve, location) => point = "getBasicTypes.pointAt";
  [@bs.send]
  external getPointAtOffset: (curve, offset) => point =
    "getBasicTypes.pointAt";
  [@bs.send]
  external getTangentAt: (curve, location) => tangent = "getTangentAt";
  [@bs.send]
  external getTangentAtOffset: (curve, offset) => tangent = "getTangentAt";
  [@bs.send] external getNormalAt: (curve, location) => normal = "getNormalAt";
  [@bs.send]
  external getNormalAtOffset: (curve, offset) => normal = "getNormalAt";
  [@bs.send]
  external getWeightedTangentAt: (curve, location) => tangent =
    "getWeightedTangentAt";
  [@bs.send]
  external getWeightedTangentAtOffset: (curve, offset) => tangent =
    "getWeightedTangentAt";
  [@bs.send]
  external getWeightedNormalAt: (curve, location) => normal =
    "getWeightedNormalAt";
  [@bs.send]
  external getWeightedNormalAtOffset: (curve, offset) => normal =
    "getWeightedNormalAt";
  [@bs.send]
  external getCurvatureAt: (curve, location) => curvature = "getCurvatureAt";
  [@bs.send]
  external getCurvatureAtOffset: (curve, offset) => curvature =
    "getCurvatureAt";
  [@bs.send]
  external getPointAtTime: (curve, time) => point =
    "getBasicTypes.pointAtTime";
  [@bs.send]
  external getTangentAtTime: (curve, time) => tangent = "getTangentAtTime";
  [@bs.send]
  external getNormalAtTime: (curve, time) => normal = "getNormalAtTime";
  [@bs.send]
  external getWeightedTangentAtTime: (curve, time) => tangent =
    "getWeightedTangentAtTime";
  [@bs.send]
  external getWeightedNormalAtTime: (curve, time) => normal =
    "getWeightedNormalAtTime";
  [@bs.send]
  external getCurvatureAtTime: (curve, time) => curvature =
    "getCurvatureAtTime";
  [@bs.send]
  external getIntersections: (curve, otherCurve) => curveLocations =
    "getIntersections"; // TODO: handle null
} = {
  type t = {
    point1: BasicTypes.point,
    point2: BasicTypes.point,
    handle1: BasicTypes.point,
    handle2: BasicTypes.point,
    segment1: Segment.t,
    path: Path.t,
    index: float,
    next: Curve.t,
    previous: Curve.t,
    selected: bool,
    values: array(float),
    points: array(BasicTypes.point),
    length: float,
    area: float,
    bounds: BasicTypes.rectangle,
    strokeBounds: BasicTypes.rectangle,
    handleBounds: BasicTypes.rectangle,
  };
  type curve = t;
  type otherCurve = t;
  type resultCurve = t;
  type segment1 = Segment.t;
  type segment2 = Segment.t;

  type point = BasicTypes.point;
  type otherPoint = BasicTypes.point;
  type point1 = BasicTypes.point;
  type point2 = BasicTypes.point;
  type handle1 = BasicTypes.point;
  type handle2 = BasicTypes.point;
  type tangent = BasicTypes.point;
  type normal = BasicTypes.point;
  type curveTimeParameters = array(float);
  type from = float;
  type to_ = float;
  type location = CurveLocation.t;
  type offset = float;
  type time = float;
  type curvature = float;
  type curveLocations = array(location);

  type info;

  [@bs.module "paper"] [@bs.new]
  external create: (segment1, segment2) => curve = "Curve";
  [@bs.module "paper"] [@bs.new]
  external createFromPoints: (point1, handle1, handle2, point2) => curve =
    "Curve";

  [@bs.send] external clone: curve => resultCurve = "clone";
  [@bs.send] external toString: curve => string = "toString";
  [@bs.send] external classify: curve => info = "classify";
  [@bs.send] external remove: curve => bool = "remove";
  [@bs.send] external isFirst: curve => bool = "isFirst";
  [@bs.send] external isLast: curve => bool = "isLast";
  [@bs.send] external getPart: (curve, from, to_) => resultCurve = "isLast";
  [@bs.send] external divideAt: (curve, location) => resultCurve = "divideAt";
  [@bs.send]
  external divideAtOffset: (curve, offset) => resultCurve = "divideAt"; // TODO: handle null
  [@bs.send]
  external divideAtTime: (curve, time) => resultCurve = "divideAtTime"; // TODO: handle null
  [@bs.send] external splitAt: (curve, location) => resultCurve = "splitAt";
  [@bs.send]
  external splitAtOffset: (curve, offset) => resultCurve = "splitAt";
  [@bs.send]
  external splitAtTime: (curve, time) => resultCurve = "splitAtTime";
  [@bs.send] external reversed: curve => resultCurve = "reversed";
  [@bs.send] external clearHandles: curve => unit = "clearHandles";

  [@bs.send] external hasHandles: curve => bool = "hasHandles";
  [@bs.send]
  external hasLength: (curve, ~epsilon: float=?, unit) => bool = "hasLength";
  [@bs.send] external isStraight: curve => bool = "isStraight";
  [@bs.send] external isLinear: curve => bool = "isLinear";
  [@bs.send] external isCollinear: (curve, otherCurve) => bool = "isCollinear";
  [@bs.send] external isHorizontal: curve => bool = "isHorizontal";
  [@bs.send] external isVertical: curve => bool = "isVertical";

  [@bs.send]
  external getLocationAt: (curve, offset) => location = "getLocationAt";
  [@bs.send]
  external getLocationAtTime: (curve, time) => location = "getLocationAtTime";
  [@bs.send]
  external getTimeAt: (curve, offset, ~start: float=?, unit) => time =
    "getTimeAt";
  [@bs.send]
  external getTimesWithTangent: (curve, tangent) => curveTimeParameters =
    "getTimesWithTangent";
  [@bs.send]
  external getOffsetAtime: (curve, time) => offset = "getOffsetAtime";
  [@bs.send]
  external getLocationOf: (curve, point) => location = "getLocationOf";
  [@bs.send] external getOffsetOf: (curve, point) => offset = "getOffsetOf";
  [@bs.send] external getTimeOf: (curve, point) => time = "getTimeOf";
  [@bs.send]
  external getNearestLocation: (curve, point) => location =
    "getNearestLocation";
  [@bs.send]
  external getNearestPoint: (curve, point) => otherPoint =
    "getNearestBasicTypes.point";
  [@bs.send]
  external getPointAt: (curve, location) => point = "getBasicTypes.pointAt";
  [@bs.send]
  external getPointAtOffset: (curve, offset) => point =
    "getBasicTypes.pointAt";
  [@bs.send]
  external getTangentAt: (curve, location) => tangent = "getTangentAt";
  [@bs.send]
  external getTangentAtOffset: (curve, offset) => tangent = "getTangentAt";
  [@bs.send] external getNormalAt: (curve, location) => normal = "getNormalAt";
  [@bs.send]
  external getNormalAtOffset: (curve, offset) => normal = "getNormalAt";
  [@bs.send]
  external getWeightedTangentAt: (curve, location) => tangent =
    "getWeightedTangentAt";
  [@bs.send]
  external getWeightedTangentAtOffset: (curve, offset) => tangent =
    "getWeightedTangentAt";
  [@bs.send]
  external getWeightedNormalAt: (curve, location) => normal =
    "getWeightedNormalAt";
  [@bs.send]
  external getWeightedNormalAtOffset: (curve, offset) => normal =
    "getWeightedNormalAt";
  [@bs.send]
  external getCurvatureAt: (curve, location) => curvature = "getCurvatureAt";
  [@bs.send]
  external getCurvatureAtOffset: (curve, offset) => curvature =
    "getCurvatureAt";
  [@bs.send]
  external getPointAtTime: (curve, time) => point =
    "getBasicTypes.pointAtTime";
  [@bs.send]
  external getTangentAtTime: (curve, time) => tangent = "getTangentAtTime";
  [@bs.send]
  external getNormalAtTime: (curve, time) => normal = "getNormalAtTime";
  [@bs.send]
  external getWeightedTangentAtTime: (curve, time) => tangent =
    "getWeightedTangentAtTime";
  [@bs.send]
  external getWeightedNormalAtTime: (curve, time) => normal =
    "getWeightedNormalAtTime";
  [@bs.send]
  external getCurvatureAtTime: (curve, time) => curvature =
    "getCurvatureAtTime";
  [@bs.send]
  external getIntersections: (curve, otherCurve) => curveLocations =
    "getIntersections"; // TODO: handle null
};

module CompoundPath: {
  type t = {
    firstSegment: Segment.t,
    lastSegment: Segment.t,
    curves: array(Curve.t),
    firstCurve: Curve.t,
    lastCurve: Curve.t,
    mutable closed: bool,
    length: float,
    area: float,
    id: float,
    className: string,
    name: string,
    mutable style: Styling.styleDescription,
    mutable locked: bool,
    mutable visible: bool,
    mutable blendMode: string,
    mutable opacity: float,
    mutable selected: bool,
    mutable clipMask: bool,
    mutable position: BasicTypes.point,
    mutable pivot: BasicTypes.point,
    mutable rotation: float,
    bounds: BasicTypes.rectangle,
    strokeBounds: BasicTypes.rectangle,
    mutable matrix: BasicTypes.matrix,
    globalMatrix: BasicTypes.matrix,
    viewMatrix: BasicTypes.matrix,
    mutable applyMatrix: bool,
    mutable strokeColor: Styling.Color.t,
    mutable fillColor: Styling.Color.t,
  };


  [@bs.deriving abstract]
  type descriptionObject = {
    [@bs.optional]
    children: array(Path.t),
    [@bs.optional]
    strokeWidth: float,
    [@bs.optional]
    strokeCap: string,
    [@bs.optional]
    strokeJoin: string,
    [@bs.optional]
    strokeScaling: bool,
    [@bs.optional]
    dashOffset: float,
    [@bs.optional]
    dashArray: array(float),
    [@bs.optional]
    miterLimit: float,
    [@bs.optional]
    fillColor: Styling.Color.t,
    [@bs.optional]
    fillRule: string,
    [@bs.optional]
    shadowColor: string,
    [@bs.optional]
    shadowBlur: float,
    [@bs.optional]
    shadowOffset: float,
    [@bs.optional]
    selectedColor: string,
  };

  [@bs.deriving abstract]
  type descriptionPointText = {
    [@bs.optional]
    children: array(PointText.t),
  };

  [@bs.module "paper"] [@bs.new]
  external create: descriptionObject => t = "CompoundPath";
  [@bs.module "paper"] [@bs.new]
  external createPointText: descriptionPointText => t = "CompoundPath";
  


  [@bs.send] external remove: t => bool = "remove";

  [@bs.get] external getPointextChildren: t => array(PointText.t) = "children";

} = {
  type t = {
    firstSegment: Segment.t,
    lastSegment: Segment.t,
    curves: array(Curve.t),
    firstCurve: Curve.t,
    lastCurve: Curve.t,
    mutable closed: bool,
    length: float,
    area: float,
    id: float,
    className: string,
    name: string,
    mutable style: Styling.styleDescription,
    mutable locked: bool,
    mutable visible: bool,
    mutable blendMode: string,
    mutable opacity: float,
    mutable selected: bool,
    mutable clipMask: bool,
    mutable position: BasicTypes.point,
    mutable pivot: BasicTypes.point,
    mutable rotation: float,
    bounds: BasicTypes.rectangle,
    strokeBounds: BasicTypes.rectangle,
    mutable matrix: BasicTypes.matrix,
    globalMatrix: BasicTypes.matrix,
    viewMatrix: BasicTypes.matrix,
    mutable applyMatrix: bool,
    mutable strokeColor: Styling.Color.t,
    mutable fillColor: Styling.Color.t,
  };

  [@bs.deriving abstract]
  type descriptionObject = {
    [@bs.optional]
    children: array(Path.t),
    [@bs.optional]
    strokeWidth: float,
    [@bs.optional]
    strokeCap: string,
    [@bs.optional]
    strokeJoin: string,
    [@bs.optional]
    strokeScaling: bool,
    [@bs.optional]
    dashOffset: float,
    [@bs.optional]
    dashArray: array(float),
    [@bs.optional]
    miterLimit: float,
    [@bs.optional]
    fillColor: Styling.Color.t,
    [@bs.optional]
    fillRule: string,
    [@bs.optional]
    shadowColor: string,
    [@bs.optional]
    shadowBlur: float,
    [@bs.optional]
    shadowOffset: float,
    [@bs.optional]
    selectedColor: string,
  };

  [@bs.deriving abstract]
  type descriptionPointText = {
    [@bs.optional]
    children: array(PointText.t),
  };


  [@bs.module "paper"] [@bs.new]
  external create: descriptionObject => t = "CompoundPath";
  [@bs.module "paper"] [@bs.new]
  external createPointText: descriptionPointText => t = "CompoundPath";

  [@bs.send] external remove: t => bool = "remove";

  
  [@bs.get] external getPointextChildren: t => array(PointText.t) = "children";

};
