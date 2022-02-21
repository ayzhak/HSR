import express from "express";
import { NoteDatastore } from "./noteDataStore.js";
import {Note} from "../models/Note.js";

export default class NoteController {
  private noteDatastore: NoteDatastore;
  constructor() {
    this.noteDatastore = new NoteDatastore();
  }

  async showAll(req: express.Request, res: express.Response) {
    // @ts-ignore
    const response = req.session.usersettings;

    const sort = {};
    let filter = {};

    // @ts-ignore
    sort[response.sortedby] = response.desc ? 1 : -1;
    if (response.hidefinished) filter = { finished: "" };

    this.noteDatastore.getAll(filter, sort).then((value) => {
      response.list = value;
      response.title = "All todo's";
      res.render("noteList", response);
    });
  }

  async showNoteCreate(req: express.Request, res: express.Response) {
    // @ts-ignore
    const response = req.session.usersettings;
    response.title = "Create new todo";
    res.render("noteEdit", response);
  }

  async createNotePost(req: express.Request, res: express.Response) {
    await this.noteDatastore.add(this.verifyNote(req.body));
    res.redirect("/");
  }

  async showNoteEditor(req: express.Request, res: express.Response) {
    // @ts-ignore
    const response = req.session.usersettings;
    response.title = "Edit todo";

    response.query = await this.noteDatastore.getById(req.params.id);
    response.action = `/edit/${response.query._id}`;
    response.showcreateddate = true;
    response.showfinished = true;

    res.render("noteEdit", response);
  }

  async editNote(req: express.Request, res: express.Response) {
    await this.noteDatastore.update(this.verifyNote(req.body));
    res.redirect(`/`);
  }

  async deleteNote(req: express.Request, res: express.Response) {
    await this.noteDatastore.delete(req.params.id);
    res.redirect("/");
  }

  private verifyNote(checkNote : any){ //Whitelist for property
    let noteModel = new Note();
    for(let propertyName in noteModel){
      // @ts-ignore
      if(noteModel[propertyName] === undefined) delete noteModel[propertyName];
    }

    return checkNote;
  }
}
