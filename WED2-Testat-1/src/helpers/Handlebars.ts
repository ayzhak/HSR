// @ts-ignore
import moment from "moment";

export function createStars(
  active: number,
  amount: number,
  direction: "left" | "right",
  options : any
) {
  if (!active && !amount && !direction) return "Please specify three parameter";
  active = Number(active);
  amount = Number(amount);
  if (active > amount) throw new Error("Can't have more active than amount.");
  if (active < 1 && amount < 1)
    throw new Error("Amount and active must be > 0.");
  let html: string = "";

  const checked = '<span class="checked-star">★</span>';
  const unchecked = '<span class="unchecked-star">☆</span>';
  for (let i = 0; i < amount; i++) {
    if (direction === "left") {
      if (active > 0) {
        html += checked;
        active--;
      } else {
        html += unchecked;
      }
    } else if (direction === "right") {
      if (active > 0) {
        html = checked + html;
        active--;
      } else {
        html = unchecked + html;
      }
    }
  }
  return html;
}

export function monthToText(dateString: string) {
  if (dateString === "") return "";

  const date = moment(dateString);

  const years = date.diff(moment(), "years");
  if (years > 1) return `in ${years} years`;
  if (years === 1) return `next year`;

  const months = date.diff(moment(), "months");
  if (months < 12 && months > 1) return `in ${months} months`;
  if (months === 1) return `next months`;

  const days = date.diff(moment(), "days");
  if (days > 1) return `in ${days} days`;
  if (days === 1) return "tomorrow";

  const hours = date.diff(moment(), "hours");
  if (hours < 24 && hours > 1) return `in ${hours} hours`;
  if (hours === 1) return "in one hour";

  const minutes = date.diff(moment(), "minutes");
  if (minutes < 60 && minutes > 0) return `in ${minutes} minutes`;
  if (minutes === 1) return "in one minute";

  return "behind schedule";
}

export function convertToChecked(str : string) {
  return str && str !== "" ? "checked" : "";
}

export function isNotUndefinedOrEmptyString(str : string) {
  return str !== undefined && str !== "";
}

export function convertToDatepickerFormat(str : string) {
  return str !== "" && !str ? "" : moment(str).format("YYYY-MM-DD");
}

export default {
  createStars,
  monthToText,
  convertToChecked,
  isNotUndefinedOrEmptyString,
  convertToDatepickerFormat,
  eq: (v1 : any, v2 : any) => v1 === v2,
  ne: (v1: any, v2: any) => v1 !== v2,
  lt: (v1 : any, v2: any) => v1 < v2,
  gt: (v1 : any, v2 : any) => v1 > v2,
  lte: (v1 : any, v2 : any) => v1 <= v2,
  gte: (v1 : any, v2 : any) => v1 >= v2,
  and() {
    return Array.prototype.every.call(arguments, Boolean);
  },
  or() {
    return Array.prototype.slice.call(arguments, 0, -1).some(Boolean);
  },
};
