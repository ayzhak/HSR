import express from "express";

type ResponseTemplate = {
    theme?: string;
    nextTheme?: string;
    sortedby?: number;
    desc?: boolean;
    hidefinished?: boolean;
    title?: string;
    list?: any;
    action?: string;
    showcreateddate?: boolean;
    showfinished?: boolean;
    query?: any;
};

export default function userSettings(req: express.Request, res: express.Response, next : express.NextFunction) {
    const usersettings: ResponseTemplate = {};
    usersettings.sortedby = sessionFilterHandler(req, "sortedby", "createdate");
    usersettings.desc = sessionFilterHandler(req, "desc", false);
    usersettings.hidefinished = sessionFilterHandler(req, "hidefinished", false);
    usersettings.theme = sessionFilterHandler(req, "theme", "day");
    usersettings.nextTheme = usersettings.theme === "day" ? "night" : "day";

    // @ts-ignore
    req.session.usersettings = usersettings;
    next()
}

function sessionFilterHandler(req : express.Request, str : string, def : any) {

    // @ts-ignore
    if (
        typeof req.query[str] === "undefined" &&
        // @ts-ignore
        typeof req.session[str] === "undefined"
    ) {
        // @ts-ignore
        req.session[str] = def;
        return def;
    }

    if (
        typeof req.query[str] !== "undefined" &&
        // @ts-ignore

        typeof req.session[str] !== "undefined"
    ) {
        // @ts-ignore
        req.session[str] = req.query[str];
        return req.query[str];
    }

    if (
        typeof req.query[str] !== "undefined" &&
        // @ts-ignore
        typeof req.session[str] === "undefined"
    ) {
        // @ts-ignore
        req.session[str] = req.query[str];
        // @ts-ignore
        return req.session[str];
    }

    if (
        typeof req.query[str] === "undefined" &&
        // @ts-ignore
        typeof req.session[str] !== "undefined"
    ) {
        // @ts-ignore
        return req.session[str];
    }

    return def;
}