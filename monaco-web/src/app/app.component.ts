import { Component } from '@angular/core';
import { Observable, of } from 'rxjs';
import { map, last } from 'rxjs/operators';
import { DisplacementService } from './displacement.service';
import { Displacement, DisplacementFeedback } from './model';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {

  readonly vehicleWidthCm = 12.0;
  readonly vehicleLengthCm = 29.0;

  readonly ratioPxPerCm = 4.0;

  readonly vehicleWidthPx = this.ratioPxPerCm * this.vehicleWidthCm;
  readonly vehicleLengthPx = this.ratioPxPerCm * this.vehicleLengthCm;

  destinationRequestX = -100;
  destinationRequestY = -100;

  currentDisplacement: Observable<Displacement> = null;

  constructor(private displacementService: DisplacementService) {
    this.currentDisplacement = displacementService.current;
    this.currentDisplacement.pipe(
      map(displacement => {
        this.destinationRequestX = this.cm2pxX(displacement.x);
        this.destinationRequestY = this.cm2pxY(displacement.y);
      })
    ).subscribe();
  }

  get windowWidth() {
    return Math.max(document.documentElement.clientWidth, window.innerWidth || 0);
  }

  get windowHeight() {
    return Math.max(document.documentElement.clientHeight, window.innerHeight || 0);
  }

  cm2pxX(dxCm) {
    return dxCm * this.ratioPxPerCm + this.windowWidth / 2;
  }

  cm2pxY(dyCm) {
    return this.windowHeight / 2 - dyCm * this.ratioPxPerCm;
  }

  px2cmX(dxPx) {
    return (dxPx - this.windowWidth / 2) / this.ratioPxPerCm;
  }

  px2cmY(dyPx) {
    return (this.windowHeight / 2 - dyPx) / this.ratioPxPerCm;
  }

  drive($event: MouseEvent) {
    const dxCm = ($event.clientX - this.windowWidth / 2) / this.ratioPxPerCm;
    const dyCm = (this.windowHeight / 2 - $event.clientY) / this.ratioPxPerCm;
    const displacementRequest = {
      x: dxCm,
      y: dyCm,
      feedback: DisplacementFeedback.NOT_STARTED.valueOf(),
    };
    console.log(displacementRequest);
    this.displacementService.updateCurrent(displacementRequest);
  }

}
