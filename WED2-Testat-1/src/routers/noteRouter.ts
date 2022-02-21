import express from "express";
import NoteController from "../controller/noteController.js";
const router = express.Router();
const noteController = new NoteController();

router.get("/", noteController.showAll.bind(noteController));
router.get("/edit/:id", noteController.showNoteEditor.bind(noteController));
router.post("/edit/:id", noteController.editNote.bind(noteController));
router.get("/create", noteController.showNoteCreate.bind(noteController));
router.post("/create", noteController.createNotePost.bind(noteController));
router.delete("/delete/:id", noteController.deleteNote.bind(noteController));

export default router;
