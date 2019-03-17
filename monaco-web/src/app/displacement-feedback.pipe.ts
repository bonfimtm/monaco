import { Pipe, PipeTransform } from '@angular/core';
import { DisplacementFeedback } from './model';

@Pipe({
  name: 'displacementFeedback'
})
export class DisplacementFeedbackPipe implements PipeTransform {

  transform(value: number): string {
    const possibleValues = Object.keys(DisplacementFeedback)
      .map(k => DisplacementFeedback[k])
      .filter(v => typeof v === 'number') as number[];
    if (
      value !== null &&
      value !== undefined &&
      possibleValues.includes(value)
    ) {
      return DisplacementFeedback[value];
    } else {
      return '?';
    }
  }

}
