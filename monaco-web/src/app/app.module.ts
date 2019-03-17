import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';

import { AngularFireModule } from '@angular/fire';
import { environment } from '../environments/environment';
import { AngularFirestore } from '@angular/fire/firestore';
import { DisplacementFeedbackPipe } from './displacement-feedback.pipe';

@NgModule({
  declarations: [
    AppComponent,
    DisplacementFeedbackPipe
  ],
  imports: [
    BrowserModule,
    AngularFireModule.initializeApp(environment.firebase),
  ],
  providers: [
    AngularFirestore,
  ],
  bootstrap: [
    AppComponent,
  ]
})
export class AppModule { }
