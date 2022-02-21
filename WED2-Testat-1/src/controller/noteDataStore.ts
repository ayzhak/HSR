// @ts-ignore
import Datastore from "nedb-promises";
// @ts-ignore
import moment from "moment";
import { Note } from "../models/Note.js";
import path from "path"

export class NoteDatastore {
  private db: Datastore;

  constructor(db? : any) {
    this.db =
      db ||
      new Datastore({ filename: path.join(__dirname, '../notes.json'), autoload: true });
  }

  async add(note : Note) {
    // @ts-ignore
    delete note._id;
    return await this.db.insert(note);
  }

  async update(toUpdate : Note) {
    const id = toUpdate._id;
    // @ts-ignore
    delete toUpdate._id;
    if (toUpdate.finished) {
      toUpdate.finished = moment().format("DD.MM.YYYY HH:mm");
    } else {
      toUpdate.finished = "";
    }
    return await this.db.update({ _id: id }, { $set: toUpdate });
  }

  async delete(id: string) {
    return this.db.remove({ _id: id }, {});
  }

  async getById(id: string) {
    return await this.db.findOne({ _id: id });
  }

  getAll(find : any, sort : any) {
    return this.db.find(find).sort(sort);
  }
}
