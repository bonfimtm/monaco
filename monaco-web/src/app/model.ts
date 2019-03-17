export enum DisplacementFeedback {
    NOT_STARTED = 0,
    MOVING = 1,
    FINISHED = 2,
}

export class Displacement {

    static readonly collectionName = 'displacement';
    static readonly currentDocId = 'current';

    x: number;
    y: number;
    feedback: DisplacementFeedback;

    constructor({ x, y, feedback }) {
        this.x = x;
        this.y = y;
        this.feedback = feedback;
    }
}
