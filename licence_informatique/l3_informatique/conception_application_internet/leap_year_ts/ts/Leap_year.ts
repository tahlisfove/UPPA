export default function Leap_year(date: string) { // ISO (used by XML): "2020-05-04"
    const milliseconds: number = Date.parse(date);
    if (isNaN(milliseconds)) {
        throw new Error("Invalid format... " + date);
    }
    const date_: Date = new Date(milliseconds);
    if ((date_.getFullYear() % 4 === 0) && (date_.getFullYear() % 100 !== 0) || (date_.getFullYear() % 400 === 0))
        return true;
    return false;
}

