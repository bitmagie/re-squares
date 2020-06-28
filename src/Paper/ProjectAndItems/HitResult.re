type t = {
    type_: string,
    name: string,
    item: Item.t,
    location: Paths.CurveLocation.t,
    color: Styling.Color.t,
    segment: Paths.Segment.t,
    point: BasicTypes.Point.t
};