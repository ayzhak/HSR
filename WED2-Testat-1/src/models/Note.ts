import moment from "moment";
export class Note {
  public _id : string;
  public finished : string;
  public createdate : string;
  public title : string;
  public description : string;
  public priority : number;
  public due : string;

  constructor(
    title: string = "",
    description: string = "",
    priority: number = 0,
    due : string = ""
  ) {
    this._id = "";
    this.createdate = moment().format("DD.MM.YYYY HH:mm");
    this.finished = "";
    this.title = title;
    this.description = description;
    this.priority = priority;
    this.due = due;
  }
}
