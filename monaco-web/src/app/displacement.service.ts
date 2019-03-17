import { Injectable } from '@angular/core';

import { AngularFirestore, AngularFirestoreDocument } from '@angular/fire/firestore';

import { Displacement } from './model';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class DisplacementService {

  private currentDoc: AngularFirestoreDocument<Displacement>;
  current: Observable<Displacement>;

  constructor(private afs: AngularFirestore) {
    this.currentDoc = afs.doc<Displacement>(`${Displacement.collectionName}/${Displacement.currentDocId}`);
    this.current = this.currentDoc.valueChanges();
  }
  updateCurrent(doc: Displacement) {
    return this.currentDoc.update(doc);
  }
}
